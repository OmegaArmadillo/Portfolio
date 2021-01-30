//*****************************************************************
// Name: Matthew Hibner
// Class: CS162 Spring 2017
// Class time: 10:00AM
// Date:  6/4/17
// Project #: Final
// Driver Name:NewFinalPanel
// Program Description:armor subclass
//*****************************************************************

public class armor extends item
{
	private String defense;
	private String atype;

	public armor(String newItemType, String newItemName, String newItemDefense)
	{
	super(newItemName);
	atype = newItemType;
	defense = newItemDefense;
	}

		public String toString()
		{
			String itemdescription = itemname + " Type: " + atype + " Defense: " + defense;
		return itemdescription;
	}
}