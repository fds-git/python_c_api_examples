import numpy as np 
import npconverter
import time
import json
import random
import uuid
from uuid import uuid4

#---------------------------------------------------

# data = np.array([np.random.randn() for _ in range(100000)])

# start = time.time()
# res = npconverter.sum(data)
# print(f"Time = {time.time() - start}")
# print(f"Result = {res}")

#---------------------------------------------------

# data = np.random.rand(20)
# print(f"data = {data}")
# print(type(data))
# res = npconverter.np_double(data)
# print(f"res = {res}")
# print(type(res))

#---------------------------------------------------

# start = time.time()
# for i in range(10000):
#     data_1 = np.random.rand(10000)
#     data_2 = np.random.rand(10000)
#     res = npconverter.np_concat(data_1, data_2)
# print(f"Time = {time.time() - start}")

#print(f"data_1 = {data_1}")
#print(f"data_2 = {data_2}")
#print(f"res = {res}")

#---------------------------------------------------

# start = time.time()
# for i in range(10000):
#     data = np.random.rand(100000)
#     res = npconverter.sum(data)
# print(f"Own numpy sum = {time.time() - start}")

# start = time.time()
# for i in range(10000):
#     data = np.random.rand(100000)
#     res = np.sum(data)
# print(f"Numpy sum = {time.time() - start}")

#----------------Сравнение написанного и встроенного методов конвертации----------------

# start = time.time()
# data_1 = np.random.rand(100000)
# data_2 = np.random.rand(100000)
# res = npconverter.get_dict(data_1, data_2)
# print(f"Own numpy numpy to dict = {time.time() - start}")

# start = time.time()
# result = [{'id': a, 'similarity': b} for a, b in zip(data_1, data_2)]
# print(f"Stock numpy to dict = {time.time() - start}")

# start = time.time()
# result = []
# for a, b in zip(data_1, data_2):
#     result.append({'id': a, 'similarity': b})
# print(f"Stock bad numpy to dict = {time.time() - start}")

# start = time.time()
# result = []
# for a, b in zip(data_1, data_2):
#     d = {}
#     d['id'] = a
#     d['similarity'] = b
#     result.append({'id': a, 'similarity': b})
# print(f"Stock bad bad numpy to dict = {time.time() - start}")

#--------------------------Возврат строки json--------------------------------

# start = time.time()
# data_1 = np.random.rand(1000)
# data_2 = np.random.rand(1000)
# str = npconverter.get_str(data_1, data_2)
# #print(f"Str = {time.time() - start}")
# print(f'str: {str}')
# json_object = json.loads(str)
# print(f'python: {json_object}')
# print(type(json_object))
# #print(type(json_object['Similarity']))

#--------------------------Arrays to JSON--------------------------------

# num_vectors = 10000
# num_lists = 10
# similarities = np.random.rand(num_vectors)
# face_ids = np.array([i for i in range(num_vectors)])
# list_ids = np.array([random.randint(0, num_lists) for i in range(num_vectors)])
# for i in range(1):
#     print('---------------------JSON-C-----------------------------')
#     start = time.time()
#     str = npconverter.arrays_to_json(similarities, list_ids, face_ids)
#     print(f"C time: {time.time() - start}")
#     print('---------------------PyObject-----------------------------')
#     start = time.time()
#     res_dict = npconverter.arrays_to_dict(similarities, list_ids, face_ids)
#     print(f"PyObject time: {time.time() - start}")
#     print('--------------------Pure python------------------------------')
#     start = time.time()
#     res = [{'id': id, 'similarity': sim} for id, sim in zip(face_ids, similarities)]

#     print(f"Python time: {time.time() - start}")


#--------------------------Test MATCHER---------------------------------------------

num_vectors = 3_000_000
num_lists = 1000
similarities = np.random.rand(num_vectors)
face_ids = np.array([uuid4().hex for i in range(num_vectors)])
list_ids = np.array([random.randint(0, num_lists-1) for i in range(num_vectors)])
list_ids_to_rearch = np.array([i for i in range(num_lists)])
max_list_index = np.max(list_ids)
limit = 5

#print(face_ids)
start = time.time()
result = npconverter.match_result(similarities, list_ids, face_ids, list_ids_to_rearch, max_list_index, limit)
print(f"Total match time: {time.time() - start}")
#print(result[1])

#-------------------Сложение 2-х numpy массивов------------------------

# a = np.array([1,2,3,4,5]*1_000_000, dtype=np.double)
# b = np.array([5,4,3,2,1]*1_000_000, dtype=np.double)
# start = time.time()
# res = npconverter.add_arrays(a, b)
# print(f"Time: {time.time() - start}")
# print(f"Test 7: {a} + {b} = {res} {type(res)}")