#include "principal.h"
#include "ui_principal.h"


#include "QDebug"

Principal::Principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    setWindowTitle("Agenda telefónica");
    // Configurar la tabla
    ui->tblLista->setColumnCount(4);
    QStringList titulo;
    titulo << "Nombre" << "Apellido" << "Teléfono" << "E-mail";
    ui->tblLista->setHorizontalHeaderLabels(titulo);
    // Leer desde el archivo
    cargarContactos();

}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_btnAgregar_clicked()
{
    // Crear y mostrar el dialogo
    PersonaDialog pd(this);
    pd.setWindowTitle("Agregar contacto");
    // Abrir la ventana y evaluar respuesta
    int res = pd.exec();
    if (res == QDialog::Rejected){
        return;
    }
    // Recuperar el objeto del cuadro de dialogo
    Persona *p = pd.persona();
    /*QString nombre = pd.nombre();
    QString apellido = pd.apellido();
    QString telefono = pd.telefono();
    QString email = pd.email();
    //Agregar a la tabla*/
    int fila = ui->tblLista->rowCount();
    ui->tblLista->insertRow(fila);
    ui->tblLista->setItem(fila, NOMBRE, new QTableWidgetItem(p->nombre()));
    ui->tblLista->setItem(fila, APELLIDO, new QTableWidgetItem(p->apellido()));
    ui->tblLista->setItem(fila, TELEFONO, new QTableWidgetItem(p->telefono()));
    ui->tblLista->setItem(fila, EMAIL, new QTableWidgetItem(p->email()));

}


void Principal::on_btnGuardar_clicked()
{
    // Verificar que exista datos para guardar
    int filas = ui->tblLista->rowCount();
    if (filas == 0){
        QMessageBox::warning(this,"Guardar contactos","Agenda sin datos para guardar");
        return;
    }
    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&archivo);
        for (int i=0; i<filas; i++) {
            QTableWidgetItem *nombre = ui->tblLista->item(i, NOMBRE);
            QTableWidgetItem *apellido = ui->tblLista->item(i, APELLIDO);
            QTableWidgetItem *telefono = ui->tblLista->item(i, TELEFONO);
            QTableWidgetItem *email = ui->tblLista->item(i, EMAIL);
            salida << nombre->text() << ";" << apellido->text() << ";";
            salida << telefono->text() << ";" << email->text() << "\n";
        }
        archivo.close();
        QMessageBox::information(this,"Guardar contactos","Contactos guardados con éxito");
    }else{
        QMessageBox::critical(this,"Guardar contactos", "No se puede escribir sobre " + ARCHIVO);
    }

}

void Principal::cargarContactos()
{
    // Verificar si el archivo existe
    QFile archivo(ARCHIVO);
    if (!archivo.exists())
        return;

    // cargar datos
    if (archivo.open(QFile::ReadOnly)) {
        QTextStream entrada(&archivo);
        int fila;
        while(!entrada.atEnd()){
            QString linea = entrada.readLine();
            QStringList datos = linea.split(";");
            //Agregar a la tabla
            fila = ui->tblLista->rowCount();
            ui->tblLista->insertRow(fila);
            ui->tblLista->setItem(fila, NOMBRE, new QTableWidgetItem(datos[NOMBRE]));
            ui->tblLista->setItem(fila, APELLIDO, new QTableWidgetItem(datos[APELLIDO]));
            ui->tblLista->setItem(fila, TELEFONO, new QTableWidgetItem(datos[TELEFONO]));
            ui->tblLista->setItem(fila, EMAIL, new QTableWidgetItem(datos[EMAIL]));
        }
        archivo.close();
    }
}

