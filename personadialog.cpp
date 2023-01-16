#include "personadialog.h"
#include "ui_personadialog.h"

PersonaDialog::PersonaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonaDialog)
{
    ui->setupUi(this);
}

PersonaDialog::~PersonaDialog()
{
    delete ui;
}

/*QString PersonaDialog::nombre()
{
    return ui->inNombre->text();
}

QString PersonaDialog::apellido()
{
    return ui->inApellido->text();
}

QString PersonaDialog::telefono()
{
    return ui->inTelefono->text();
}

QString PersonaDialog::email()
{
    return ui->inEmail->text();
}*/

void PersonaDialog::on_buttonBox_accepted()
{
    /*REFACTORIZACIÓN: Se cambia el código para mejorar la funcionalidad dentro de el, no cambia sus funciones
    externas*/
    QString nombre =  ui->inNombre->text();
    QString apellido =  ui->inApellido->text();
    QString telefono =  ui->inTelefono->text();
    /*if (!telefono.contains("1", Qt::CaseInsensitive)){
        QMessageBox::warning(this, "Adventencia", "El campo del telefono debe contener solo numeros");
        return;
    }*/
    QString email =  ui->inEmail->text();

    if (nombre.isEmpty()|| apellido.isEmpty() || telefono.isEmpty() || email.isEmpty()){
        QMessageBox::warning(this,"Advertencia","Debe completar todos los mensajes de texto");
        return;
    }

    for(int i=0; i<nombre.length(); i++)
    {
        if(nombre[i].isDigit())
        {
            QMessageBox::warning(this,"Advertencia","El campo de texto\"Nombre\"solo admite letras");
            return;
        }
    }

    for (int i=0; i<apellido.length(); i++)
    {
        if(apellido[i].isDigit())
        {
            QMessageBox::warning(this,"Advertencia","El campo de texto\"Apellido\"solo admite letras");
            return;
        }
    }

    for (int i=0; i<telefono.length(); i++)
    {
        if(!telefono[i].isDigit())
        {
            QMessageBox::warning(this,"Advertencia","El campo de texto\"Teléfono\"solo admite números");
            return;
        }
    }
    bool a=false, b=false;
    for (int i=0; i<email.length(); i++)
    {
        if(email[i]=="@")
        {
            a=true;
        }
        if(email[i]==".")
        {
           b=true;
        }
    }
    if(a==false||b==false)
    {
       QMessageBox::warning(this,"Advertencia","El campo de texto\"email\"está incorrecto");
       return;
    }

    this->m_persona = new Persona(nombre, apellido, telefono, email);
    accept();
}


void PersonaDialog::on_buttonBox_rejected()
{
    reject();
}

Persona *PersonaDialog::persona() const
{
    return m_persona;
}
