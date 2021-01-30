//*****************************************************************
// Name: Matthew Hibner
// Class: CS162 Spring 2017
// Class time: 10:00AM
// Date:  6/4/17
// Project #: Final
// Driver Name:NewFinalPanel
// Program Description:weapon subclass
//*****************************************************************

public class weapon extends item
{
private String damage;
private String wtype;

public weapon(String newItemType, String newItemName, String newItemDamage)
{
super(newItemName);
wtype = newItemType;
damage = newItemDamage;
}

	public String toString()
	{
		String itemdescription = itemname + " Type: " + wtype + " Damage: " + damage;
	return itemdescription;
	}

}