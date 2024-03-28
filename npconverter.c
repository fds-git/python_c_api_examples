#define NPY_NO_DEPRECATED_API NPY_1_10_API_VERSION

#include <Python.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <numpy/arrayobject.h>
#include <stdio.h>
#include <json-c/json.h>
#include <time.h>
#include <sys/time.h>

PyObject *add (PyObject *self, PyObject *args) {
    double x;
    double y;
    PyArg_ParseTuple(args, "dd", &x, &y);
    return PyFloat_FromDouble(x + y);
}

static PyObject *sum(PyObject *self, PyObject *args) {
    PyArrayObject *arr;
    PyArg_ParseTuple(args, "O", &arr);
    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(arr) || PyArray_TYPE(arr) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    double *data = PyArray_DATA(arr);
    int64_t size  = PyArray_SIZE(arr);

    double total = 0;
    for (int i = 0; i < size; ++i) {
        total += data[i];
    }
    return PyFloat_FromDouble(total);
}

static PyObject *np_double(PyObject *self, PyObject *args) {
    PyArrayObject *arr;
    PyArg_ParseTuple(args, "O", &arr);
    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(arr) || PyArray_TYPE(arr) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    double *data = PyArray_DATA(arr);
    int64_t size  = PyArray_SIZE(arr);

    npy_intp dims[] = {[0] = size};
    PyObject *result = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    double *result_data = PyArray_DATA((PyArrayObject*)result);

    for (int i = 0; i < size; ++i) {
        result_data[i] = 2 * data[i];
    }
    return result;
}

static PyObject *np_concat(PyObject *self, PyObject *args) {
    PyArrayObject *arr1;
    PyArrayObject *arr2;
    PyArg_ParseTuple(args, "OO", &arr1, &arr2);
    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(arr1) || PyArray_TYPE(arr1) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr1)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    if (!PyArray_Check(arr2) || PyArray_TYPE(arr2) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr2)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    double *data_1 = PyArray_DATA(arr1);
    int64_t size_1  = PyArray_SIZE(arr1);

    double *data_2 = PyArray_DATA(arr2);
    int64_t size_2  = PyArray_SIZE(arr2);

    int64_t size = size_1 + size_2;

    npy_intp dims[] = {[0] = size_1 + size_2};
    PyObject *result = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    double *result_data = PyArray_DATA((PyArrayObject*)result);

    for (int i = 0; i < size_1; ++i) {
        result_data[i] = data_1[i];
    }

    for (int i = 0; i < size_2; ++i) {
        result_data[i + size_1] = data_2[i];
    }

    return result;
}

static PyObject *add_arrays(PyObject *self, PyObject *args) {
    PyArrayObject *arr1;
    PyArrayObject *arr2;
    PyArg_ParseTuple(args, "OO", &arr1, &arr2);
    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(arr1) || PyArray_TYPE(arr1) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr1)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    if (!PyArray_Check(arr2) || PyArray_TYPE(arr2) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr2)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    double *data_1 = PyArray_DATA(arr1);
    int64_t size_1  = PyArray_SIZE(arr1);

    double *data_2 = PyArray_DATA(arr2);
    int64_t size_2  = PyArray_SIZE(arr2);

    //int64_t size = size_1 + size_2;

    npy_intp dims[] = {[0] = size_1};
    PyObject *result = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    double *result_data = PyArray_DATA((PyArrayObject*)result);

    for (int i = 0; i < size_1; ++i) {
        result_data[i] = data_1[i] + data_2[i];
    }

    return result;
}


static PyObject* get_dict(PyObject* self, PyObject* args)
{
    PyArrayObject *arr1;
    PyArrayObject *arr2;
    PyArg_ParseTuple(args, "OO", &arr1, &arr2);
    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(arr1) || PyArray_TYPE(arr1) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr1)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    if (!PyArray_Check(arr2) || PyArray_TYPE(arr2) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(arr2)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    double *data_1 = PyArray_DATA(arr1);
    int64_t size_1  = PyArray_SIZE(arr1);

    double *data_2 = PyArray_DATA(arr2);
    int64_t size_2  = PyArray_SIZE(arr2);

    int result_list_lenght;
    if (size_1 <= size_2)
        result_list_lenght = size_1;
    else
        result_list_lenght = size_2;

    PyObject* python_list = PyList_New(result_list_lenght);

    for (int i = 0; i < result_list_lenght; i++)
    {
        PyObject* python_dict = Py_BuildValue("{s:f, s:f}", "id", data_1[i], "similarity", data_2[i]);
        PyList_SetItem(python_list, i, python_dict);
    }

    return python_list;
}

static PyObject* get_str(PyObject* self, PyObject* args)
{
    float similarity = 3.14;
    int id = 1;
    char text[] = "[{\"face_id\": 1, \"similarity\": 3.22}]";

    return Py_BuildValue("s", text);
}

static PyObject* arrays_to_json(PyObject* self, PyObject* args)
{   
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    PyArrayObject *similarities;
    PyArrayObject *list_ids;
    PyArrayObject *face_ids;
    PyArg_ParseTuple(args, "OOO", &similarities, &list_ids, &face_ids);
    gettimeofday(&stop, NULL);
    printf("parsing %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(similarities) || PyArray_TYPE(similarities) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(similarities)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    if (!PyArray_Check(list_ids) || PyArray_TYPE(list_ids) != NPY_LONG || !PyArray_IS_C_CONTIGUOUS(list_ids)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type int");
        return NULL;
    }
    if (!PyArray_Check(face_ids) || PyArray_TYPE(face_ids) != NPY_LONG || !PyArray_IS_C_CONTIGUOUS(face_ids)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }
    gettimeofday(&stop, NULL);
    printf("checking %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    double *similarities_arr = PyArray_DATA(similarities);
    int64_t size_similarities_arr = PyArray_SIZE(similarities);

    int64_t *list_ids_arr = PyArray_DATA(list_ids);
    int64_t size_list_ids_arr = PyArray_SIZE(list_ids);

    int64_t *face_ids_arr = PyArray_DATA(face_ids);
    int64_t size_face_ids_arr = PyArray_SIZE(face_ids);
    gettimeofday(&stop, NULL);
    printf("type casting %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    const char *filename = "json_out.json";
    json_object *root = json_object_new_object();
    if (!root)
        return Py_BuildValue("s", "pisdetz");
    
    json_object *vectors = json_object_new_array();

    for (int i = 0; i < size_similarities_arr; i++)
    {
        json_object *vector = json_object_new_object();
        json_object_object_add(vector, "id", json_object_new_int(face_ids_arr[i]));
        json_object_object_add(vector, "similarity", json_object_new_double(similarities_arr[i]));
        json_object_array_add(vectors, vector);
    }

    json_object_object_add(root, "aa", vectors);
    gettimeofday(&stop, NULL);
    printf("json constructing %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    const char *res = json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY);
    gettimeofday(&stop, NULL);
    printf("json to string %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    PyObject* result = Py_BuildValue("s", res);
    gettimeofday(&stop, NULL);
    printf("string to python string %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    return result;
}

static PyObject* arrays_to_dict(PyObject* self, PyObject* args)
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    PyArrayObject *similarities;
    PyArrayObject *list_ids;
    PyArrayObject *face_ids;
    PyArg_ParseTuple(args, "OOO", &similarities, &list_ids, &face_ids);
    gettimeofday(&stop, NULL);
    printf("parsing %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(similarities) || PyArray_TYPE(similarities) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(similarities)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    if (!PyArray_Check(list_ids) || PyArray_TYPE(list_ids) != NPY_LONG || !PyArray_IS_C_CONTIGUOUS(list_ids)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type int");
        return NULL;
    }
    if (!PyArray_Check(face_ids) || PyArray_TYPE(face_ids) != NPY_LONG || !PyArray_IS_C_CONTIGUOUS(face_ids)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type int");
        return NULL;
    }
    gettimeofday(&stop, NULL);
    printf("checking %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    double *similarities_arr = PyArray_DATA(similarities);
    int64_t size_similarities_arr = PyArray_SIZE(similarities);

    int64_t *list_ids_arr = PyArray_DATA(list_ids);
    int64_t size_list_ids_arr = PyArray_SIZE(list_ids);

    int64_t *face_ids_arr = PyArray_DATA(face_ids);
    int64_t size_face_ids_arr = PyArray_SIZE(face_ids);
    gettimeofday(&stop, NULL);
    printf("type casting %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    PyObject* python_list = PyList_New(size_similarities_arr);

    for (int i = 0; i < size_similarities_arr; i++)
    {
        PyObject* python_dict = Py_BuildValue("{s:i, s:f}", "id", face_ids_arr[i], "similarity", similarities_arr[i]);
        PyList_SetItem(python_list, i, python_dict);
    }
    PyObject* result = Py_BuildValue("{s:O}", "sdfsd", python_list);
    gettimeofday(&stop, NULL);
    printf("Pyobject constructing %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    return result;
}

static PyObject* match_result(PyObject* self, PyObject* args)
{
    // Важное замечание:
    // После выражения PyList_Append(list, item); нужно выполнить PyDECREF(item);, так как PyList_Append при добавлении item автоматически
    // увеличит колечество ссылок на содержимое item на 1 (будет равно 2). Если не выполнить PyDECREF, то будет утечка памяти (после удаления list 
    // счетчик ссылок на содержимое item уменьшится на 1 (станет равным 1), и это содержимое навсегда останется в памяти)
    // После использования PyList_SET_ITEM и PyTuple_SET_ITEM не нужно выполнить PyDECREF(item);, так как эти функции не выполняют инкремент 
    // самостоятельно в отличие от PyList_Append. Если после них выполнить PyDECREF(item);, счетчик ссылок на содержимое станет равным 0,
    // и может возникнуть "Access after free". Зато можно делать так: PyList_SET_ITEM(list, i, Py_BuildValue("i", item)) (в одну строку).
    // Py_BuildValue увеливает число ссылок на содержимое переданного в нее PyObject (если PyObject передавался). Поэтому нужно выполнить декремент.
    // числа ссылок на содержимое PyObject.
    // PyArg_ParseTuple не увеливает число ссылок на содержимое переданного в нее PyObject. Нельзя выполнять декремент после PyArg_ParseTuple,
    // количество ссылок может стать равным 0.
    // PyDict_SetItem(result_dict, key_o, value_o); увеливает число ссылок на ключ и значение на 1. 
    // Поэтому надо выполнять Py_DECREF(value_o); Py_DECREF(key_o);
    // На утечки тестировать скрипт в Jupyter Notebook
    struct timeval stop, start;
    int max_list_index;
    int limit;
    PyArrayObject *similarities;
    PyArrayObject *list_ids;
    PyArrayObject *face_ids;
    PyArrayObject *list_ids_to_rearch;
    PyArg_ParseTuple(args, "OOOOii", &similarities, &list_ids, &face_ids, &list_ids_to_rearch, &max_list_index, &limit);

    if (PyErr_Occurred()) {
        return NULL;
    }
    // PyArray_IS_C_CONTIGUOUS - массив не должен быть срезом
    if (!PyArray_Check(similarities) || PyArray_TYPE(similarities) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(similarities)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }

    if (!PyArray_Check(list_ids) || PyArray_TYPE(list_ids) != NPY_LONG || !PyArray_IS_C_CONTIGUOUS(list_ids)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type int");
        return NULL;
    }
    if (!PyArray_Check(face_ids) || PyArray_TYPE(face_ids) != NPY_UNICODE || !PyArray_IS_C_CONTIGUOUS(face_ids)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type numpy.str");
        return NULL;
    }

    if (!PyArray_Check(list_ids_to_rearch) || PyArray_TYPE(list_ids_to_rearch) != NPY_LONG || !PyArray_IS_C_CONTIGUOUS(list_ids_to_rearch)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a С-contiguous numpy array of type double");
        return NULL;
    }
    
    gettimeofday(&start, NULL);
    double *similarities_arr = PyArray_DATA(similarities);
    int64_t size_similarities_arr = PyArray_SIZE(similarities);

    int64_t *list_ids_arr = PyArray_DATA(list_ids);
    int64_t size_list_ids_arr = PyArray_SIZE(list_ids);

    int64_t *list_ids_to_rearch_arr = PyArray_DATA(list_ids_to_rearch);
    int64_t size_list_ids_to_rearch = PyArray_SIZE(list_ids_to_rearch);

    gettimeofday(&stop, NULL);
    printf("type casting %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    //Формируем вспомогательный массив (не забыть free)
    int * helper;
    helper = calloc(max_list_index, sizeof(int));

    if (helper == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    //Заполняем его значениями limit в тех ячейках, индекс которых
    //равен значениям из list_ids_to_rearch
    for(int i = 0; i < size_list_ids_to_rearch; i++)
        helper[list_ids_to_rearch_arr[i]] = limit;
    gettimeofday(&stop, NULL);
    printf("creating helper array %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    // Формируем итоговую структуру Dict[List] (пустую)
    // ключ - индекс листа из list_ids_to_rearch_arr
    // значение - python List (пустой).
    gettimeofday(&start, NULL);
    PyObject* result_dict = PyDict_New();
    for(int i = 0; i < size_list_ids_to_rearch; i++) {
        int key = list_ids_to_rearch_arr[i];
        PyObject* key_o = Py_BuildValue("i", key);
        PyObject* value_o = PyList_New(0);
        PyDict_SetItem(result_dict, key_o, value_o);
        Py_DECREF(value_o);
        Py_DECREF(key_o);
    }
    gettimeofday(&stop, NULL);
    printf("create empty result %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    for (long int i = 0; i < size_similarities_arr; i++)
    {
        int list_idx = list_ids_arr[i];
        if (helper[list_idx]) {
            helper[list_idx]--;
            PyObject* uuid = PyArray_GETITEM(face_ids, PyArray_GetPtr(face_ids, &i));
            PyObject* python_dict = Py_BuildValue("{s:O, s:f}", "id", uuid, "similarity", similarities_arr[i]);
            Py_DECREF(uuid);
            PyObject* key_o = Py_BuildValue("i", list_idx);
            PyObject* python_list = PyDict_GetItem(result_dict, key_o);
            Py_DECREF(key_o);
            PyList_Append(python_list, python_dict);
            Py_DECREF(python_dict);
        }
        else {
            continue;
        }
    }
    gettimeofday(&stop, NULL);
    printf("filling result %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    free(helper);
    return result_dict;
}

static PyMethodDef methods[] = {
    {"add", add, METH_VARARGS, "Adds two numbers together"},
    {"add_arrays", add_arrays, METH_VARARGS, "Add two Numpy arrays"},
    {"np_concat", np_concat, METH_VARARGS, "Concat two numpy arrays"},
    {"sum", sum, METH_VARARGS, "Calculate sum of numpy array"},
    {"np_double", np_double, METH_VARARGS, "Double elements in numpy array"},
    {"get_dict", get_dict, METH_VARARGS, "Convert two numpy arrays to list of dict"},
    {"get_str", get_str, METH_VARARGS, "Convert numpy to string"},
    {"arrays_to_json", arrays_to_json, METH_VARARGS, "Convert numpy arrays to dict via JSON"},
    {"arrays_to_dict", arrays_to_dict, METH_VARARGS, "Convert numpy arrays to dict"},
    {"match_result", match_result, METH_VARARGS, "Get result for matcher"},
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef npconverter = {
    PyModuleDef_HEAD_INIT,
    "npconverter",
    "This is a module named npconverter",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_npconverter() {
    //printf("Hello world\n");
    PyObject *module = PyModule_Create(&npconverter);
    import_array();
    return module;
}
