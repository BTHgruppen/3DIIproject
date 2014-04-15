--------------------------------------------------
==================================================
3D II PROJEKT GUIDELINES (Jonas Notation)
==================================================

--------------------------------------------------

==================================================
FUNCTION LAYOUT
==================================================

Should look something like this (Functions start with a capital letter):
```cpp
int Add(int a, int b)
{
	// Code goes here

	for(int i = 0; i < m_something; i++)
	{
		// Other code goes here.
	}
}
```

==================================================
VARIABLE NAMES
==================================================

--------------------------------------------------
GLOBAL VARIABLES

Projectwide global variables should be avoided, but if necessary they are to be preceded by "g_".

For example:
```cpp
int g_globalVariableName;

class Class
{
	// Code goes here.
};
```
--------------------------------------------------
MEMBER VARIABLES

Member variables (such as variables local to a class), should be preceded by "m_".

For example: 
```cpp
class Class
{
	int m_memberVariableName;

	// Code goes here.
};
```
--------------------------------------------------
LOCAL VARIABLES

Local variables (such as temporary variables used i functions), should be preceded by "l_".
Except if the name is very short, such as "i".

For example:
```cpp
if()
{
	int l_localVariableName;
	int i;
}
```
--------------------------------------------------
PARAMETERS

Functions input parameters should be preceded by "p_".
Exceptions are few letter names such as "i" or "x".

For Example:
```cpp
void AddToArray(int p_input, int p_location)
{
	m_array[p_location] = p_input;
}
```
--------------------------------------------------