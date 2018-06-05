# Pythonize C++
C++ with a snake face.

## WARNINGS!
* Since *int* is redefined<sup>1</sup> in \<pythnized/integer>, there may be problems with C macros like htons(). In this case, it is recommended to drop ancient pure C libraries or encapsulate the problematic macro before including \<pythonized>.
* For the same reason, templates with parameters of type *int* will not work. It is recommended to include \<pythonize> the last and use *auto* instead of *int* in template parameters.

___

1 — Yes, redefining *int* **is** necessary — in order to make expressions like ‘a = int(input())’ legal.
