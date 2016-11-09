#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QByteArray>
#include "qrencode/qrencode.h"
#include <QSerialPortInfo>
#include "Barcode.h"
#include <QtDebug>
#include <QDateTime>
#include <QProcess>
#include <QString>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->InitStyle();
    this->InitForm();
    barcode = new BarCode(this);
    barcode->setVisible(false);
    typedef QPair<BarCode::BarcodeTypes, QString> BarcodeType;
    BarCode::BarcodeTypePairList typeList = BarCode::getTypeList();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InitStyle()
{
    this->location = this->geometry();
    this->setProperty("Form", true);
    this->setProperty("CanMove", true);
    this->setWindowTitle(EXE_NAME);
}


void MainWindow::InitForm()
{
   this->rencode_text  ="";
   this->rencode_text_2="";
   QRcode_Encode(this->rencode_text);
   QRcode_Encode_2(this->rencode_text_2);

   //设置调试窗口的字体大小
   ui->plainTextEdit->setFont(QFont( "宋体" , 10 ,  QFont::Normal) );
   log_output(tr("启动..."));
   QFile file("macAdress.txt");
   if(!file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
   {
        qDebug()<<"open file failure";
   }
   if(ui->checkBox->isChecked())
   {
       ui->rencode_lineEdit_2->setVisible(true);
       ui->rencode_view_2->setVisible(true);
   }
   else
   {
       ui->rencode_lineEdit_2->setVisible(false);
       ui->rencode_view_2->setVisible(false);
   }
}
//显示条形码
void MainWindow::QBarcode_ts102(QByteArray &text)
{
    ui->rencode_lineEdit->setText(text);
    if (this->rencode_text.trimmed().isEmpty())
        return;
    QImage barcodeImage(ui->rencode_view->size(), QImage::Format_ARGB32);
    barcodeImage.fill(QColor(255, 255, 255, 0));
    QPainter painter(&barcodeImage);
    barcode->setBarcodeType((BarCode::BarcodeTypes)60);
    barcode->setValue(this->rencode_text);
    barcode->drawBarcode(&painter, 0, 0, barcodeImage.width(), barcodeImage.height());
    painter.end();
    ui->rencode_view->setPixmap(QPixmap::fromImage(barcodeImage));
}

void MainWindow::QPcode( QPrinter *printer,QPainter *painter,QByteArray &text)
{
    QPen pen;
    QFont font;
    int margin = 1;//设置图像的页边距大小
    ui->rencode_lineEdit->setText(text);
    this->foreground = QColor("black");
    this->background = QColor("white");

    QRcode *qrcode = QRcode_encodeString(text.data(), 1, QR_ECLEVEL_L, QR_MODE_8, 1);
    if(NULL != qrcode) {
        painter->begin(printer);
        QRect pRect = painter->viewport();
        painter->setViewport(pRect.x(),pRect.y(),VIEWSIZE_WITH,VIEWWIZE_HIGHT);
        painter->setWindow(pRect.x(),pRect.y(),WINDONWSIZE_WITH,WINDONWSIZE_HIGHT);
        painter->translate(0, 0);//先回到坐标原点
        painter->save();
        //画二维码
        unsigned char *point = qrcode->data;
        painter->translate(S_LEFT_MARGIN, S_UP_MARGIN);//坐标平移，向右是X，向下是Y
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->background);
        painter->drawRect(0, 0, S_TWODIMENSION_SIZE, S_TWODIMENSION_SIZE);
        double scale = (S_TWODIMENSION_SIZE - 2.0 * margin) / qrcode->width;
        painter->setBrush(this->foreground);
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    QRectF r(margin + x * scale, margin + y * scale, scale, scale);
                    painter->drawRects(&r, 1);
                }
                point ++;
            }
        }
        //打印文字
        painter->restore();
        painter->translate(S_LEFT_MARGIN_TEXT, S_TWODIMENSION_SIZE+S_UP_MARGIN+S_PITURE_B_TEXT);
        pen.setColor(QColor("#ff00ff"));
        pen.setWidth(1);
        painter->setPen(pen);
        font.setBold(false);
        font.setPointSize(S_TEXT_SIZE);//设置字体大小
        font.setFamily("新宋体");
        painter->setFont(font);
        painter->drawText(0,0,text);
        //结束打印
        painter->end();
        point = NULL;
        //把mac地址保存到文件里面
        QFile file("macAdress.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
        {
            QTextStream stream( &file );
            stream << text << "\r\n";
            file.close();
        }
        else
        {
            log_output(tr("打开文件失败..."));
        }
        QRcode_free(qrcode);
    }
}
void MainWindow::QPcode_2( QPrinter *printer,QPainter *painter,QByteArray &text,QByteArray &text_2)
{
    int margin = D_MARGIN_VALUE;//设置图像的页边距大小
    ui->rencode_lineEdit->setText(text);
    this->foreground = QColor("black");
    this->background = QColor("white");
    QPen pen;
    QFont font;

    printer->logicalDpiX();

    QRcode *qrcode = QRcode_encodeString(text.data(), 1, QR_ECLEVEL_L, QR_MODE_8, 1);
    if(NULL != qrcode) {
        painter->begin(printer);
        QRect pRect = painter->viewport();
        painter->setViewport(pRect.x(),pRect.y(),VIEWSIZE_WITH,VIEWWIZE_HIGHT);
        painter->setWindow(pRect.x(),pRect.y(),WINDONWSIZE_WITH,WINDONWSIZE_HIGHT);
        painter->translate(0,0);//移动到原点
        painter->save();//缓存当前的坐标状态
        qDebug("printer.x %d printer.y %d",printer->pageRect().x(),printer->pageRect().y());
        qDebug("printer.w %d printer.h %d",printer->pageRect().width(),printer->pageRect().height());
        //画二维码
        unsigned char *point = qrcode->data;
        painter->translate(D_LEFT_MARGIN,D_UP_MARGIN);//坐标平移，向右是X，向下是Y
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->background);
        painter->drawRect(0, 0, D_TWODIMENSION_SIZE, D_TWODIMENSION_SIZE);
        double scale = (D_TWODIMENSION_SIZE - 2.0 * margin) / qrcode->width;
        painter->setBrush(this->foreground);
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    QRectF r(margin + x * scale, margin + y * scale, scale, scale);
                    painter->drawRects(&r, 1);
                }
                point ++;
            }
        }
        //打印文字
        painter->restore();//回到save的位置
        painter->save();//缓存当前的坐标状态
        painter->translate(D_LEFT_MARGIN,D_TWODIMENSION_SIZE+D_UP_MARGIN+D_PITURE_B_TEXT);
        pen.setColor(QColor("#ff00ff"));
        pen.setWidth(1);
        painter->setPen(pen);
        font.setBold(false);
        font.setPointSize(D_TEXT_SIZE);//设置字体大小
        font.setFamily("新宋体");
        painter->setFont(font);
        painter->drawText(0,0,text);

        qDebug("printer.x %d printer.y %d",printer->pageRect().x(),printer->pageRect().y());
        qDebug("printer.w %d printer.h %d",printer->pageRect().width(),printer->pageRect().height());
        //打印二维码
        painter->restore();//回到save的位置
        painter->save();//缓存当前的坐标状态
        painter->translate(D_LEFT_MARGIN+D_TWODIMENSION_SIZE+D_TWODIMENSION_INTERVAL,D_UP_MARGIN);//坐标平移，向右是X，向下是Y
        QRcode *qrcode2 = QRcode_encodeString(text_2.data(), 1, QR_ECLEVEL_L, QR_MODE_8, 1);
        if(NULL != qrcode2) {
            unsigned char *point = qrcode2->data;
            painter->setPen(Qt::NoPen);
            painter->setBrush(this->background);
            painter->drawRect(0, 0, D_TWODIMENSION_SIZE, D_TWODIMENSION_SIZE);
            double scale = (D_TWODIMENSION_SIZE - 2.0 * margin) / qrcode2->width;
            painter->setBrush(this->foreground);
            for (int y = 0; y < qrcode2->width; y ++) {
                for (int x = 0; x < qrcode2->width; x ++) {
                    if (*point & 1) {
                        QRectF r(margin + x * scale, margin + y * scale, scale, scale);
                        painter->drawRects(&r, 1);
                    }
                    point ++;
                }
            }
        }
        //打印文字
        painter->restore();//回到save的位置
        painter->save();//缓存当前的坐标状态
        painter->translate(D_LEFT_MARGIN+D_TWODIMENSION_SIZE+D_TWODIMENSION_INTERVAL,D_TWODIMENSION_SIZE+D_UP_MARGIN+D_PITURE_B_TEXT);
        pen.setColor(QColor("#ff00ff"));
        pen.setWidth(1);
        painter->setPen(pen);
        font.setBold(false);
        font.setPointSize(D_TEXT_SIZE);//设置字体大小
        font.setFamily("新宋体");
        painter->setFont(font);
        painter->drawText(0,0,text_2);
        //结束打印
        painter->end();
        point = NULL;
        //把mac地址保存到文件里面
        QFile file("macAdress.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
        {
            QTextStream stream( &file );
            stream << text << "\r\n";
            stream << text_2 << "\r\n";
            file.close();
        }
        else
        {
            log_output(tr("打开文件失败..."));
        }
        QRcode_free(qrcode);
    }
}
//二维码显示
void MainWindow::QRcode_Encode(QByteArray &text)
{
    int margin = D_MARGIN_VALUE;
    ui->rencode_lineEdit->setText(text);
    this->foreground = QColor("black");
    this->background = QColor("white");
    QRcode *qrcode = QRcode_encodeString(text.data(), 1, QR_ECLEVEL_L, QR_MODE_8, 1);
    if(NULL != qrcode) {
        QPixmap pixmap(IMAGE_SIZE,IMAGE_SIZE);//ui->rencode_view->width(), ui->rencode_view->height());
        QPainter painter;
        painter.begin(&pixmap);
        unsigned char *point = qrcode->data;
        painter.setPen(Qt::NoPen);
        painter.setBrush(this->background);
        painter.drawRect(0, 0, IMAGE_SIZE, IMAGE_SIZE);
        double scale = (IMAGE_SIZE - 2.0 * margin) / qrcode->width;
        painter.setBrush(this->foreground);
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    QRectF r(margin + x * scale, margin + y * scale, scale, scale);
                    painter.drawRects(&r, 1);
                }
                point ++;
            }
        }
        ui->rencode_view->setPixmap(pixmap);
        painter.end();
        point = NULL;
        QRcode_free(qrcode);
    }
}

void MainWindow::FrameParse(char c)
{
    switch (state) {
    case 0:
        if(c=='#')
         {
           this->recv_arr.clear();
           state++;
         }

        break;
    case 1:
        if(c=='#')
        {
            if(ui->checkBox->isChecked())
            {
                static unsigned char dcount=0;
                if(dcount==0)
                {
                    dcount=1;
                    this->rencode_text.clear();
                    this->rencode_text = this->recv_arr;
                    if(rencode_text.isEmpty()==false)
                    {
                    QRcode_Encode(this->rencode_text);//显示二维码
                    log_output(tr("解析成功"));
                    }
                }
                else if(dcount==1)
                {
                    dcount=0;
                    this->rencode_text_2.clear();
                    this->rencode_text_2 = this->recv_arr;
                    if(rencode_text_2.isEmpty()==false)
                    {
                    QRcode_Encode_2(this->rencode_text_2);//显示二维码
                    log_output(tr("解析成功"));
                    }
                }
            }
            else
            {
                this->rencode_text.clear();
                this->rencode_text = this->recv_arr;
                if(rencode_text.isEmpty()==false)
                {
                QRcode_Encode(this->rencode_text);//显示二维码
                log_output(tr("解析成功"));
                }
            }
            state = 0;
        }else
        {
           this->recv_arr.append(c);
        }

        break;
    default:
        state = 0;
        break;
    }

}

void MainWindow::log_output(QString info)
{
    QString time= QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss");
    ui->plainTextEdit->appendPlainText(tr("[%1]\r\n%2").arg(time).arg (info));
}


void MainWindow::plotPic(QPrinter *printer)
{
    log_output("开始打印...");
}
//函 数 名：HexToAsc()
//功能描述：把16进制转换为ASCII
char MainWindow::IntToStr(char aChar)
{
    char ss;
    printf("%s %d\n",__FUNCTION__,aChar);
    switch(aChar)
    {
        case 0: ss= '0';break;
        case 1: ss= '1';break;
        case 2: ss= '2';break;
        case 3: ss= '3';break;
        case 4: ss= '4';break;
        case 5: ss= '5';break;
        case 6: ss= '6';break;
        case 7: ss= '7';break;
        case 8: ss= '8';break;
        case 9: ss= '9';break;

        case 10: ss= 'A';break;
        case 11: ss= 'B';break;
        case 12: ss= 'C';break;
        case 13: ss= 'D';break;
        case 14: ss= 'E';break;
        case 15: ss= 'F';break;
        default:break;
    }
    printf("%s %c\n",__FUNCTION__,ss);
    return ss;
}
//函 数 名：StrToInt()
//功能描述：把字符转换成对应的数字，比如a转换成10
char MainWindow::StrToInt(char aChar)
{
    char ss;
    printf("%s %c\n",__FUNCTION__,aChar);
    switch(aChar)
    {
        case '0': ss= 0;break;
        case '1': ss= 1;break;
        case '2': ss= 2;break;
        case '3': ss= 3;break;
        case '4': ss= 4;break;
        case '5': ss= 5;break;
        case '6': ss= 6;break;
        case '7': ss= 7;break;
        case '8': ss= 8;break;
        case '9': ss= 9;break;

        case 'A': ss= 10;break;
        case 'B': ss= 11;break;
        case 'C': ss= 12;break;
        case 'D': ss= 13;break;
        case 'E': ss= 14;break;
        case 'F': ss= 15;break;
        default:break;
    }
    printf("%s %d\n",__FUNCTION__,ss);
    return ss;
}
//函 数 名：HexToAsc()
//功能描述：把16进制转换为ASCII
char IntToStr(unsigned char aChar){
    char ss;
    switch(aChar)
    {
        case 0: ss= '0';break;
        case 1: ss= '1';break;
        case 2: ss= '2';break;
        case 3: ss= '3';break;
        case 4: ss= '4';break;
        case 5: ss= '5';break;
        case 6: ss= '6';break;
        case 7: ss= '7';break;
        case 8: ss= '8';break;
        case 9: ss= '9';break;

        case 10: ss= 'A';break;
        case 11: ss= 'B';break;
        case 12: ss= 'C';break;
        case 13: ss= 'D';break;
        case 14: ss= 'E';break;
        case 15: ss= 'F';break;
        default:break;
    }
    //printf("%c\n",ss);
    return ss;
}
//char *str=(char*)malloc(4*2);
char * HexToString(char *str,unsigned char Hex[],unsigned char lenth)
{
    unsigned char i=0,j=0;
    unsigned char tema,temp;
    //char *str=(char*)malloc(lenth*2);
    for(i=0;i<lenth;i++)
    {
        tema=(Hex[i]>>4)&0x0F;
        str[j]=IntToStr(tema);
        j++;
        temp=Hex[i]&0x0F;
        str[j]=IntToStr(temp);
        j++;
    }
    str[j]='\0';
    return str;
}

void MainWindow::on_print_button_clicked()
{
   /*##################输入数据判断###################*/
   QTime t;
   t= QTime::currentTime();
   qsrand(t.msec()+t.second()*1000);
   QByteArray readCmdMac="DD54";
   static int macValue=0x10000001;//初始值
   QString sValue=ui->textEdit->text();
   qDebug()<<sValue;
   if((sValue.length()<12))
   {
       QMessageBox::warning(this,tr("ERROR"),tr("MAC地址长度有误"));
       return;
   }
   else if(!((sValue.contains("DD54"))||(sValue.contains("dd54"))))
   {
       QMessageBox::warning(this,tr("ERROR"),tr("MAC地址前面没有DD54"));
       return;
   }

   QString stringMacValue=sValue.right(8);
   qDebug()<<stringMacValue;
   bool ok;
   macValue=stringMacValue.toLong(&ok,16);
   qDebug()<<macValue;
   qDebug("%x\r\n",macValue);
   int imacStep=ui->textEdit_2->text().toInt();
   qDebug()<<imacStep;
   int imacCount=ui->textEdit_3->text().toInt();
   qDebug()<<imacCount;
for(int imac=0;imac<imacCount;imac++)
{
    //第一次数据##########################################
    readCmdMac="DD54";
    qDebug()<<QString::number(macValue,16).toUpper();
    readCmdMac.append(QString::number(macValue,16).toUpper().toLatin1());
    qDebug()<<readCmdMac;
    {// 生成随机数######################
           int intQrand=qrand()%65535;
           QString stringQrand=QString::number(intQrand,16).toUpper();
           QString stringQrandS;
           switch(stringQrand.length())
           {
               case 0: stringQrandS="0000";break;
               case 1: stringQrandS="000"+stringQrand;break;
               case 2: stringQrandS="00"+stringQrand;break;
               case 3: stringQrandS="0"+stringQrand;break;
               case 4: stringQrandS=stringQrand;break;
               default: stringQrandS=stringQrand; qDebug()<<"over 65535"; break;
           }
           qDebug()<<stringQrandS;
    QByteArray qbyteMacAndQrad=readCmdMac.append(stringQrandS.toLatin1());
    ui->rencode_lineEdit->setText(qbyteMacAndQrad);
    this->rencode_text=qbyteMacAndQrad;
    qDebug()<<this->rencode_text;
    }
    //在PC界面显示二维码
    QRcode_Encode(this->rencode_text);
    log_output(tr("-->1:")+readCmdMac);

    //第二次数据##########################################
    macValue+=imacStep;
    readCmdMac="DD54";
    readCmdMac.append(QString::number(macValue,16).toUpper().toLatin1());
    qDebug()<<readCmdMac;

    {// 生成随机数######################
               int intQrand=qrand()%65535;
               QString stringQrand=QString::number(intQrand,16).toUpper();
               QString stringQrandS;
               switch(stringQrand.length())
               {
                   case 0: stringQrandS="0000";break;
                   case 1: stringQrandS="000"+stringQrand;break;
                   case 2: stringQrandS="00"+stringQrand;break;
                   case 3: stringQrandS="0"+stringQrand;break;
                   case 4: stringQrandS=stringQrand;break;
                   default: stringQrandS=stringQrand; qDebug()<<"over 65535"; break;
               }
               qDebug()<<stringQrandS;
    QByteArray qbyteMacAndQrad=readCmdMac.append(stringQrandS.toLatin1());
    ui->rencode_lineEdit_2->setText(qbyteMacAndQrad);
    this->rencode_text_2=qbyteMacAndQrad;
    qDebug()<<this->rencode_text_2;
    }
    //在PC界面显示二维码
    QRcode_Encode_2(this->rencode_text_2);
    log_output(tr("-->2:")+readCmdMac);
    ui->print_button->setText("打印");
    macValue+=imacStep;
    //二维码打印///////////////////////////////////////////////////
    static long prinCount=0;
    QPrinter printer;
    //设置纸张大小
    printer.setPageSize(QPagedPaintDevice::Custom);
    printer.setPaperSize(QSizeF(PAPER_WIDTH,PAPER_HIGHT),QPrinter::Millimeter);

    qDebug("printer.x %d printer.y %d",printer.pageRect().x(),printer.pageRect().y());
    qDebug("printer.w %d printer.h %d",printer.pageRect().width(),printer.pageRect().height());
    QString printerName = printer.printerName();
    if(printerName.size()==0)
    {
        log_output("请连接打印机!!!!!");
        return;
    }
    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("print Document");
    QPrintDialog dlg(&printer,this);
    QPainter painter;

    if(ui->checkBox->isChecked())
    {
        prinCount++;
        log_output(tr("[两张]打印第 ")+QString::number(prinCount)+tr(" 次"));
        QPcode_2(&printer,&painter,this->rencode_text,this->rencode_text_2);
    }
    else
    {
        prinCount++;
        log_output(tr("[单张]打印第 ")+QString::number(prinCount)+tr(" 次"));
        QPcode(&printer,&painter,this->rencode_text);
    }
    ui->textEdit->setText("DD54"+QString::number(macValue,16));
}
}
//二维码显示
void MainWindow::QRcode_Encode_2(QByteArray &text)
{
    int margin = D_MARGIN_VALUE;
    ui->rencode_lineEdit_2->setText(text);
    this->foreground = QColor("black");
    this->background = QColor("white");
    QRcode *qrcode = QRcode_encodeString(text.data(), 1, QR_ECLEVEL_L, QR_MODE_8, 1);
    if(NULL != qrcode) {
        QPixmap pixmap(IMAGE_SIZE,IMAGE_SIZE);//ui->rencode_view->width(), ui->rencode_view->height());
        QPainter painter;
        painter.begin(&pixmap);
        unsigned char *point = qrcode->data;
        painter.setPen(Qt::NoPen);
        painter.setBrush(this->background);
        painter.drawRect(0, 0, IMAGE_SIZE, IMAGE_SIZE);
        double scale = (IMAGE_SIZE - 2.0 * margin) / qrcode->width;
        painter.setBrush(this->foreground);
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    QRectF r(margin + x * scale, margin + y * scale, scale, scale);
                    painter.drawRects(&r, 1);
                }
                point ++;
            }
        }
        ui->rencode_view_2->setPixmap(pixmap);
        painter.end();
        point = NULL;
        QRcode_free(qrcode);
    }
}

void MainWindow::on_rencode_lineEdit_2_textChanged(const QString &arg1)
{
    //QRcode_Encode_2();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        log_output("打印两张...");
        ui->rencode_lineEdit_2->setVisible(true);
        ui->rencode_view_2->setVisible(true);
    }
    else
    {
        log_output("打印单张...");
        ui->rencode_lineEdit_2->setVisible(false);
        ui->rencode_view_2->setVisible(false);
    }
}
