
Tech stack:

- c++
- 


Should be compatible with Windows, MacOS, Linux

**Features** 
- The ability to add custom profiles, with different financial information
- Persistent memory using json
- Easy to use commands (eg, it asks for an expense, you say $50, it asks you how often it's deposisted, you can type like 30 days or 2 months or 3 years (or even just like 30d, 2m, 3y)



**If we have more time:**

- Encryption/Decryption to hide sensitive financial data
- A login for profiles

** Function Signatures **

mainMenu()
expenseMenu()


Shows the 



Classes:

class Profile

    Variables:
    
    Expenses[] (Data structure holding Expense objects, likely vector (or maybe set as it's unordered)
    string name
    int salary
    int salaryFreq
    
    
    
    
    Arguments:
    addProfile()
        Adds a profile (Does not allow an already existing profile to be added)
    deleteProfile()
        Deletes profile (denies if you're currently on the profile)
    getProfile()
    


Interface

    Variables:
        Profile[] (Saves all profiles)
        Profile activeProfile

    Arguments:
        setActiveProfile()
        mainMenu()
            Shows the main menu
        expenseMenu()
            Shows the menu to add an expense
        salaryMenu()
            Shows menu to change your salary
        analysisScreen()
            Shows the main analysis screen
        interestMenu()
            Allows you to calculate interest (linear or compound)
        
        
        

Expense

Variables:
    int dailyCost (To be saved in days, to be calculated from weeks, years etc when it's added)
    string name
    string[] tags

    
    
    
Arguments:
    getExpense(string name)
    setExpense(int cost, string name, string[] tags)
    getExpenseCost()
    getExpenseTags()
    

    



Commands:

`profile add <name>`
Adds a profile

`profile delete <name>`
Deletes a profile (Denies if you are in the profile)

`profile <name>`
Switches the active profile to profile <name>

`
