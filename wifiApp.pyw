import sys, serial
from PyQt4 import QtGui
##ser = serial.Serial('COM3',115200)

info = []

class Example(QtGui.QWidget):
    
    def __init__(self):
        super(Example, self).__init__()
        
        self.initUI()
        
    def initUI(self):      

        self.btn = QtGui.QPushButton('Wifi ID', self)
        self.btn.move(20, 20)
        self.btn.clicked.connect(self.showDialog)

        self.btn1 = QtGui.QPushButton('Password',self)
        self.btn1.move(20, 50)
        self.btn1.clicked.connect(self.showDialog1)

        self.btn2 = QtGui.QPushButton('Choose your Port',self)
        self.btn2.move(20, 80)
        self.btn2.clicked.connect(self.getItem)

        self.btn2 = QtGui.QPushButton('Connect', self)
        self.btn2.move(75, 110)
        self.btn2.clicked.connect(self.connectWifi)
        
        self.le = QtGui.QLineEdit(self)
        self.le.move(130, 22)

        self.le1 = QtGui.QLineEdit(self)
        self.le1.move(130, 52)

        self.le2 = QtGui.QLineEdit(self)
        self.le2.move(130, 82)
        
        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle('Wifi Config')
        self.show()



    

    def showDialog(self):
        
        user_id, ok = QtGui.QInputDialog.getText(self, 'WiFi Name', 
            'Enter your Wifi ID:')
        
        if ok:
            self.le.setText(str(user_id))

        info.append(user_id)
           

    def showDialog1(self):
        
        user_pw, ok = QtGui.QInputDialog.getText(self, 'WiFi Password', 
            'Enter your Password:')
        
        if ok:
            self.le1.setText(str(user_pw))

        info.append(user_pw)

    def getItem(self):

        ports = ("COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9","COM10","COM11","COM12")

        port, ok = QtGui.QInputDialog.getItem(self, "Communication Port", 
         "List of COM Ports", ports, 0, False)

        if ok and port:
            self.le2.setText(port)

        
        info.append(port)
        
    def connectWifi(self):
        s = serial.Serial(info[2], 115200)
        s.write(info)
        print(info)
     
  
       

        
def main():
    
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
