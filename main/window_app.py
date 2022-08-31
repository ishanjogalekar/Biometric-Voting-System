import tkinter as tk
import time
root= tk.Tk()
root.title('Voting System')

canvas1 = tk.Canvas(root, width = 300, height = 300)
canvas1.pack()
count = 1


def hello1():  
   label1 = tk.Label(root, text= 'Voting Done', fg='blue', font=('helvetica', 12, 'bold'))
   canvas1.create_window(150, 200, window=label1)
   with open('out.txt', 'a') as f:
    f.write("Candidate 1: "+str(count)+"\n")
   # time.sleep(2.5)
   root.destroy()

def hello2():  
   label1 = tk.Label(root, text= 'Voting Done', fg='blue', font=('helvetica', 12, 'bold'))
   canvas1.create_window(150, 200, window=label1)
   
   with open('out.txt', 'a') as f:
    f.write("Candidate 2: "+str(count)+"\n")
   # time.sleep(2.5)
   root.destroy() 

def hello3():  
   label1 = tk.Label(root, text= 'Voting Done', fg='blue', font=('helvetica', 12, 'bold'))
   canvas1.create_window(150, 200, window=label1)
   
   with open('out.txt', 'a') as f:
    f.write("Candidate 3: "+str(count)+"\n")
   # time.sleep(2.5)
   root.destroy() 

def hello4():  
   label1 = tk.Label(root, text= 'Voting Done', fg='blue', font=('helvetica', 12, 'bold'))
   canvas1.create_window(150, 200, window=label1)
   with open('out.txt', 'a') as f:
    f.write("Candidate 4: "+str(count)+"\n")
   
   # time.sleep(2.5)
   root.destroy()


def run_app():
    button1 = tk.Button(text='Candidate 1', command=hello1, bg='brown',fg='white')
    button2 = tk.Button(text='Candidate 2', command=hello2, bg='brown',fg='white')
    button3 = tk.Button(text='Candidate 3', command=hello3, bg='brown',fg='white')
    button4 = tk.Button(text='Candidate 4', command=hello4, bg='brown',fg='white')
    canvas1.create_window(150, 20, window=button1)
    canvas1.create_window(150, 60, window=button2)
    canvas1.create_window(150, 100, window=button3)
    canvas1.create_window(150, 140, window=button4)
    root.mainloop()

if __name__ == '__main__':
    run_app()
    print('Vote Valid')
