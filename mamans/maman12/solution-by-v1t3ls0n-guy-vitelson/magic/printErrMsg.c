
#include "data.h"
Bool handleInputError(Error err)
{
    printf("\n### Input Error! ###\n");
    switch (err)
    {

    case notAnInteger:
    {
        printf("Not an integer number!\n");
        break;
    }
    case generalInputError:
    {
        printf("Only numbers and white space characters allowed!\n");
        break;
    }
    case tooManyNumbers:
    {
        printf("You have inserted too many numbers!\n");

        break;
    }
    case notEnoughNumbers:
    {
        printf("You did not inserted enough numbers!\n");
        break;
    }

    default:
        break;
    }

    return False;
}