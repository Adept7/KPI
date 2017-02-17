# -*- coding: utf-8 -*-
import view
import base

command = 0
command2 = 0


def command_func(com):
    global command2
    com = view.main_menu()
    if com == 1:
        base.view_base()
        return 1
    if com == 2:
        command2 = view.sec_menu()
        if command2 == 1:
            base.new_faculty()
        if command2 == 2:
            base.new_group()
        return 1
    if com == 3:
        command2 = view.sec_menu()
        if command2 == 1:
            base.change_faculty()
        if command2 == 2:
            base.change_group()
        return 1
    if com == 4:
        command2 = view.sec_menu()
        if command2 == 1:
            base.del_faculty()
        if command2 == 2:
            base.del_group()
        return 1
    if com == 5:
        base.filter()
        return 1
    if com == 6:
        base.save_base()
        return 1
    if com == 7:
        base.refresh_from_f()
        return 1
    if com == 8:
        base.del_base()
        return 1
    if com == 9:
        return 0

    if com in range(1, 8):
        print("Неверный номер, попробуйте еще.")

while 1 == 1:
    if command_func(command) == 0:
        break

print("program is finished")
