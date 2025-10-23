
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


int dailyCost;
    The cost of the expense in days, the user should be able to type how often the payment is, and this value should be converted to per day for consistancy and stored here.
string name;
    The name of the expense
vector<string> tags;
    Users can set tags for expenses (eg, "personal", "bills", "taxes")


Expense();
    Empty initialiser
Expense(int cost, string name, vector<string> tags);
    Initialiser

int getExpenseCost();
    Returns cost of the expense with expense.getExpenseCost();
vector<string> getExpenseTags();
    Returns a string vector of all the tags with expense,.getExpenseTags();
string getName();
    Returns name with expense.getName();

void setExpenseCost(int expenseCost);
    Sets an expense cost with expense.setExpenseCost(int e) where e is the cost of the expense in days
void setExpenseTags(vector<string> tags);
    Sets tags with expense.setExpenseTags() where e is the cost of the expense in days (Should push back each tag to the existing tag vector, not just replace it)
void setName(string name);
    Sets name with expense.setName();

Commands:

`profile add <name>`
Adds a profile

`profile delete <name>`
Deletes a profile (Denies if you are in the profile)

`profile <name>`
Switches the active profile to profile <name>

