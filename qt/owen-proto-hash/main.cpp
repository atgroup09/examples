#include <iostream>
#include <QtGlobal>
#include <QCoreApplication>
#include <QDebug>

#include "type.h"


#define OWEN_PARAM_CODE_MAX_SZ      4

#define OWEN_ERR_OK                 0x0
#define OWEN_ERR_PARAM_EMPTY        0xF3   // ""
#define OWEN_ERR_PARAM_DOT_FIRST    0xF4   // ".ParamName"
#define OWEN_ERR_PARAM_DOT_DOUBLE   0xF5   // "..ParamName"
#define OWEN_ERR_PARAM_INVALID_CHAR 0xF6
#define OWEN_ERR_PARAM_CODE_SZ      0xF7   // list of parameter code is empty or > OWEN_PARAM_CODE_MAX_SZ


quint16 encodeParamStr(const QString &ParamStrIn, QByteArray &ParamCodeIn)
{
    quint16 Result = OWEN_ERR_OK;
    quint8 i, j;
    char c, cEnc, cPrev;

    if(!ParamStrIn.isEmpty())
    {
        ParamCodeIn.clear();

        for(i=0, j=0; i<ParamStrIn.size(); i++)
        {
            c = ParamStrIn.at(i).toLatin1();

            if(c >= '0' && c <= '9')
            {
                cEnc = c-'0';
            }
            else if(c >= 'a' && c <= 'z')
            {
                cEnc = c-'a'+10;
            }
            else if(c >= 'A' && c <= 'Z')
            {
                cEnc = c-'A'+10;
            }
            else if(c == '-')
            {
                cEnc = 10+26;
            }
            else if(c == '_')
            {
                cEnc = 10+26+1;
            }
            else if(c == '/')
            {
                cEnc = 10+26+2;
            }
            else if(c == ' ')
            {
                cEnc = 10+26+3;
                break; //end of ParamName
            }
            else if(c == '.')
            {
                if(i)
                {
                    if(c == cPrev)
                    {
                        //ERROR
                        Result = OWEN_ERR_PARAM_DOT_DOUBLE;
                        break;
                    }
                }
                else
                {
                    //ERROR
                    Result = OWEN_ERR_PARAM_DOT_FIRST;
                    break;
                }

                ParamCodeIn[j-1] = cEnc+1;
                continue;
            }
            else
            {
                //ERROR
                Result = OWEN_ERR_PARAM_INVALID_CHAR;
                break;
            }

            cEnc = cEnc*2;
            ParamCodeIn[j] = cEnc;
            j++;
            cPrev = c;
        }

        for(; j<4; j++)
        {
            ParamCodeIn[j] = 78;  // ' '
        }
    }
    else
    {
        //ERROR
        Result = OWEN_ERR_PARAM_EMPTY;
    }

    return (Result);
}


quint16 hashByte(char ByteIn, quint16 HashIn)
{
    for(int i=0; i<7; i++, ByteIn<<=1)
    {
        if((ByteIn^(HashIn>>8)) & 0x80)
        {
            HashIn <<= 1;
            HashIn ^= 0x8F57;
        }
        else
        {
            HashIn <<= 1;
        }
    }

    return (HashIn);
}


quint16 hashParamCode(const QByteArray &ParamCodeIn, quint16 *HashIn)
{
    uint16_t Result = OWEN_ERR_OK;
    int sz = ParamCodeIn.size();

    if(!ParamCodeIn.isEmpty() && sz <= OWEN_ERR_PARAM_CODE_SZ)
    {
        *HashIn = 0;

        for(int i=0; i<sz; i++)
        {
            *HashIn = hashByte(ParamCodeIn[i]<<1, *HashIn);
        }
    }
    else
    {
        //ERROR
        Result = OWEN_ERR_PARAM_EMPTY;
    }

    return (Result);
}


typedef union {
    quint16 data;
    char    chars[2];
} WORD_uct;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString Param = QString("r-L");

    QByteArray ParamCode;
    quint16 Hash;
    quint16 Result;

    qDebug() << QString("%1").arg(Param);
    Result = encodeParamStr(Param, ParamCode);
    qDebug() << QString("- encodeParamStr.Result: %1").arg(QString::number(Result));
    for(int i=0; i<ParamCode.size(); i++)
    {
        qDebug() << (quint8)ParamCode.at(i);
    }

    Result = hashParamCode(ParamCode, &Hash);
    qDebug() << QString("- hashParamCode.Result: %1").arg(QString::number(Result));
    qDebug() << QString("- hash: %1").arg(QString::number(Hash, 16));

    return a.exec();
}
