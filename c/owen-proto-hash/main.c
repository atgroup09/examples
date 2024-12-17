#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define OWEN_ERR_OK                 0x0
#define OWEN_ERR_PARAM_EMPTY        0xF3   // ""
#define OWEN_ERR_PARAM_DOT_FIRST    0xF4   // ".ParamName"
#define OWEN_ERR_PARAM_DOT_DOUBLE   0xF5   // "..ParamName"
#define OWEN_ERR_PARAM_INVALID_CHAR 0xF6


uint16_t encodeParamStr(const char *ParamStrIn, int ParamStrLenIn, char *ParamCodeIn)
{
    uint16_t Result = OWEN_ERR_OK;
    int i, j;
    char b;
    char c, cPrev = ' ';

    if(ParamStrIn && ParamStrLenIn && ParamCodeIn)
    {
        for(i=0, j=0; i<ParamStrLenIn; i++)
        {
            c = toupper(ParamStrIn[i]);

            if(c >= '0' && c <= '9')
            {
                b = c-'0';
            }
            else if(c >= 'A' && c <= 'Z')
            {
                b = c-'A'+10;
            }
            else if(c == '-')
            {
                b = 10+26;
            }
            else if(c == '_')
            {
                b = 10+26+1;
            }
            else if(c == '/')
            {
                b = 10+26+2;
            }
            else if(c == ' ')
            {
                b = 10+26+3;
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

                ParamCodeIn[j-1]+= 1;
                continue;
            }
            else
            {
                //ERROR
                Result = OWEN_ERR_PARAM_INVALID_CHAR;
                break;
            }

            ParamCodeIn[j] = b*2;
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


uint16_t hashByte(char ByteIn, uint16_t HashIn)
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

uint16_t hashParamCode(const char *ParamCodeIn, uint16_t *HashIn)
{
    uint16_t Result = OWEN_ERR_OK;
    *HashIn = 0;

    if(ParamCodeIn)
    {
        for(int i=0; i<4; i++)
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


int main()
{
    char Param[10] = "rEAd";

    char ParamCode[4];
    uint16_t Hash;
    uint16_t Result;

    printf("%s\r\n", &Param[0]);
    Result = encodeParamStr(&Param[0], strlen(&Param[0]), &ParamCode[0]);
    printf("- encodeParamStr.result: %d\r\n", Result);
    for(int i=0; i<4; i++)
    {
        printf("%d ", ParamCode[i]);
    }
    printf("\r\n");

    Result = hashParamCode(&ParamCode[0], &Hash);
    printf("- hashParamCode.result: %d\r\n", Result);
    printf("- hash: 0x%04x\n\r", Hash);

    return (0);
}
