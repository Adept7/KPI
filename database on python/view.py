# -*- coding: utf-8 -*-

def main_menu():
    print("""\n
    1. Просмотреть базу
    2. Добавить новый эллемент
    3. Изменить элемент
    4. Удалить существующий элемент
    5. Отфильтровать
    6. Сохранить базу в файл
    7. Восстановить базу из файла
    8. Удалить базу
    9. Выход""")
    return  input("Введите номер запроса: ")


def sec_menu():
    print("""
        1. Факультет
        2. Группу""")
    return input("Введите номер запроса: ")

