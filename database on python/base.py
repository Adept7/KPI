# -*- coding: utf-8 -*-
import pickle

base = []


class ItemFaculty:
    def __init__(self, string, n):
        self.__name = string.upper()
        self.__num = n
        self.list = []

    def set_name(self, string):
        self.__name = string.upper()

    def get_name(self):
        return self.__name

    def set_num(self, n):
        self.__num = n

    def get_num(self):
        return self.__num


class ItemGroup:
    def __init__(self, string, c, n):
        self.__name = string.upper()
        self.__num_students = n
        self.__course = c

    def set_name(self, string):
        self.__name = string.upper()

    def get_name(self):
        return self.__name

    def set_num_students(self, ns):
        self.__num_students = ns

    def get_num_students(self):
        return self.__num_students

    def set_course(self, course):
        self.__course = course

    def get_course(self):
        return self.__course


def new_faculty():
    base.append(ItemFaculty(raw_input("Название нового факультета: ").upper(), input("количество преподавателей: ")))


def new_group():
    b = raw_input("Название факультета: ").upper()
    for i in base:
        if b == i.get_name():
            i.list.append(ItemGroup(raw_input("Название группы: ").upper(), input("курс: "), input("количество студентов: ")))
            return
    print ("Нет такого факультета.")


def change_faculty():
    b = raw_input("Название факультета: ").upper()
    for i in base:
        if b == i.get_name():
            i.set_name(raw_input("Новое название: "))
            i.set_num(raw_input("ну и количество преподавателей: "))
            return
    print ("Нет такого факультета.")


def change_group():
    b = raw_input("Название факультета: ").upper()
    for i in base:
        if b == i.get_name():

            g = raw_input("Название группы: ").upper()
            for j in i.list:
                if g == j.get_name():
                    j.set_name(raw_input("Новое название: "))
                    j.set_course(input("и курс: "))
                    j.set_num_students(input("ну и количество студентов: "))
                    return
    print ("Нет такого факультета.")


def del_faculty():
    b = raw_input("Название факультета: ").upper()
    for i in base:
        if i.get_name() == b:
            base.remove(i)
            return
    print ("Нет такого факультета.")


def del_group():
    b = raw_input("Факультет: ").upper()
    for i in base:
        if i.get_name() == b:
            g = raw_input("Группа:").upper()
            for j in i.list:
                if j.get_name() == g:
                    i.list.remove(j)
                    return
    print ("Нет такого факультета.")


def filter():
    max = 0
    for i in base:
        if len(i.list) > max:
            max = len(i.list)

    for i in base:
        if len(i.list) == max:
            print(i.get_name())


def save_base():
    f = open('base.pickle', 'wb')
    pickle.dump(base, f)
    f.close()


def refresh_from_f():
    f = open('base.pickle', 'rb')
    global base
    base = list(pickle.load(f))
    f.close()


def del_base():
    global base
    base = []
    with open('base.pickle', 'wb') as f:
        pickle.dump(base, f)


def view_base():
    if base.__len__() == 0:
        print ("База пуста")
    else:
        for i in base:
            print ("Факультет: " + i.get_name() + ", персонал " + str(i.get_num()) + " человек")
            for j in i.list:
                print (j.get_name() + "  " + str(j.get_course()) + " курс  " + str(j.get_num_students()) + " человек")
            print




