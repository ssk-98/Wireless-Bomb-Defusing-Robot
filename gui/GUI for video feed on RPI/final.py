#!/usr/bin/env python3
import numpy as np
import cv2
from tkinter import *

def change_color():
    cc=Tk()
    cc.title("COLORS")
    cc_b1=Radiobutton(cc, text="RED",value=1,command=set_color_red).pack(anchor=W)
    cc_b2=Radiobutton(cc, text="BLUE",value=2, command=set_color_blue).pack(anchor=W)
    cc_b3=Radiobutton(cc, text="GREEN",value=3, command=set_color_green).pack(anchor=W)
    cc_b4=Radiobutton(cc, text="GREY",value=4,command=set_color_grey).pack(anchor=W)
    cc_b6=Radiobutton(cc,text='DEFAULT',value=5,command=set_color_black).pack(anchor=W)
    cc_b5=Button(cc,text="SAVE", command=cc.destroy)
    cc_b5.pack()
    cc.mainloop()

def set_color_red():
        top.configure(background='red')

def set_color_blue():
    top.configure(background='blue')

def set_color_green():  
    top.configure(background='green')
    
def set_color_grey():
    top.configure(background='grey')
def set_color_black():
    top.configure(background='black')
    
def change_dimensions(p):
    cd=Tk()
    cd.title("DEFAULT DIMENSIONS")
    Label(cd, text="WIDTH").grid(row=0)
    Label(cd, text="HEIGHT").grid(row=1)
    w=Entry(cd)
    h=Entry(cd)
    def testing_get():
        global a, b
        a=w.get()
        b=h.get()
        if p:
            f=open("dim.config","w")
            f.write(a+" ")
            f.write(b)
            f.close()
        cd.destroy()
    w.grid(row=0, column=1)
    h.grid(row=1, column=1)
    cd_b=Button(cd, text="SAVE", command=testing_get)
    cd_b.grid(row=2,column=1)
    cd.mainloop()

def testing_get():
    global a, b
    a=w.get()
    b=h.get()
    f=open("dim.config","w")
    f.write(a+" ")
    f.write(b)
    f.close()
    cd.destroy()

def launch_live_feed():
    cap=cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, int(a))
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT,int(b))
    while True:
        ret,frame= cap.read()
        cv2.imshow('LIVEFEED',frame)
        if cv2.waitKey(20) & 0xFF==ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()


def use_default():
    global a,b
    f=open("dim.config","r")
    a,b=f.read().split()
    f.close()

    
top=Tk()
top.title("WIRELESS BOMB DEFUSING ROBOT")
b1=Radiobutton(top, text="USE CUSTOM DIMENSIONS",bg='yellow',value=1,command=lambda: change_dimensions(0)).place(relx=0.5,rely=0.3,anchor="center")
b2=Radiobutton(top, text="USE DEFAULT DIMENSIONS",bg='yellow',value=2, command=use_default).place(relx=0.5,rely=0.5,anchor="center")
b3=Button(top,text="LAUNCH LIVE FEED", bg='yellow',command=launch_live_feed).place(relx=0.5,rely=0.9,anchor="center")

menubar= Menu(top)
SETTINGS=Menu(menubar, tearoff=0)
SETTINGS.add_command(label="CHANGE DEFAULT DIMENSIONS",command=lambda: change_dimensions(1))
SETTINGS.add_command(label="CHANGE BACKGROUND COLOR", command=change_color)
menubar.add_cascade(label="SETTINGS",menu=SETTINGS)
'''
C = Canvas(top, bg="blue", height=250, width=300)
filename = PhotoImage(file="b.png")
background_label = Label(top, image=filename)
background_label.place(x=0, y=0,relwidth=1, relheight=1)

C.pack()'''
top.config(menu=menubar,background='black')
top.mainloop()
