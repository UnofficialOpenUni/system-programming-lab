#include <math.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

int htoi (char s[])
{
	int i, power, n;
	i=power=n=0;
	
	if (s[i++]=='0')
	{
		if (s[i]=='X')
		{
			for (i=2; s[i]!='\0'; ++i)
				;
			--i;
			while (i>=2)
			{
				n += (isdigit(s[i])) ? (s[i]-'0')*(int)pow(FACTOR, power++): (s[i]>='A' && s[i]<='F') ? 
				(s[i]-CAP_TO_HX)*(int)pow(FACTOR, power++): 0;
				
				--i;
			}
				/* experiment
				if (isdigit(s[i]))
					n += (s[i]-'0') * (pow(FACTOR, power++));
				else if (s[i]>='A' && s[i]<='F')
					n += (s[i]-CAP_TO_HX) * (pow(FACTOR, power++));
				*/
					
		}
		else if (s[i]=='x')
		{
			for (i=2; s[i]!='\0'; ++i)
				;
			--i;
			while (i>=2)
			{
				n += (isdigit(s[i])) ? (s[i]-'0') * (int)pow(FACTOR, power++): (s[i]>='a' && s[i]<='f') ? 
				(s[i]-NONCAP_TO_HX) * (int)pow(FACTOR, power++): 0;
				
				--i;
			}
				
		}
		
	}
	
	return n;
}
