==================================================
PROJECT GUIDELINES
==================================================
--------------------------------------------------
--------------------------------------------------

==================================================
GIT BRANCHING (using GIT BASH command line)
==================================================
--------------------------------------------------
1. At the start of your work, get the latest commits with:
    ```
        git pull --prune
    ```
2. Create your own branch to work in, name it whatever you want:
    ```
        git checkout yourBranchName
    ```
3. Write your code, don't forget to do small commits often.
    ```
        git commit -m "Commit description"
    ```
If GIT states that there are changes, use:
    ```
        git add -p
    ```
to go through a list of changes.
4. You can review your changes by using:
    ```
        git diff
    ```
and
    ```
        git status
    ```
5. When you are ready to push to the master branch, use:
    ```
        git checkout master
    ```
,
    ```
        git pull --prune
    ```
,
    ```
        git checkout yourBranchName
    ```
,
    ```
        git rebase master
    ```
6. If you get any conflicts, solve these and then make sure the program runs. If it does, merge your branch:
    ```
        git checkout master
    ```
,
    ```
        git merge yourBranchName
    ```
,
    ```
        git push
    ```
7. Finally, close your branch: 
    ```
        git branch -d yourBranchName
    ```

--------------------------------------------------

==================================================
FUNCTION LAYOUT
==================================================
--------------------------------------------------
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
--------------------------------------------------

==================================================
VARIABLE NAMES
==================================================
--------------------------------------------------
* GLOBAL VARIABLES

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
* MEMBER VARIABLES

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
* LOCAL VARIABLES

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
* PARAMETERS

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