1//*****************************************************************
// Name: Matthew Hibner
// Class: CS162 Spring 2017
// Class time: 10:00AM
// Date:  6/4/17
// Project #: Final
// Driver Name:NewFinalPanel
// Program Description:
//	Allows for creation of a character sheet using buttons and text fields
//	The top row is for basic information
//	The left side rolls numbers for character stats
//	The center is the character inventory
// 	The right side lets you add items to the inventory based on what item you want
//	The bottom saves the character information to a file Character.txt
//*****************************************************************

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Scanner;
import java.util.Random;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;



public class NewFinalPanel extends JPanel
{

		// array that keeps the character stats
		static int[] statsInt = new int[6];
		//int that represents the current stat being edited
		static int currentstat;
		//generator that generates the numbers of the stat
		static Random roll = new Random();

		//labels for to show the values of the stats in the stats array
		static JLabel stat1 = new JLabel("Not yet rolled");
		static JLabel stat2 = new JLabel("Not yet rolled");
		static JLabel stat3 = new JLabel("Not yet rolled");
		static JLabel stat4 = new JLabel("Not yet rolled");
		static JLabel stat5 = new JLabel("Not yet rolled");
		static JLabel stat6 = new JLabel("Not yet rolled");

		//array of labels that represent the items in the inventory
		static JLabel[] invs = {new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),new JLabel("nothing"),};

		// string that keeps track of the character name
		static String name = "No Name Chossen";

		// string that keeps track of the character race
		static String race = "No race chossen";

		// string that keeps track of the character class
		static String classes = "No class chossen";

		//the string that will get the int from the text field and the int to keep track of the character level
		static int level = 0;
		static String levelString;

		// string that keeps track of the character allignment
		static String allignment = "No Allignment";

		//array of items that is the character inventory
		static item[] inventory = new item[10];


		//the radio buttons that change what kind of item is being added to the inventory
		JRadioButton itemRadio = new JRadioButton("Basic Item");
		JRadioButton armorRadio = new JRadioButton("Armor");
		JRadioButton weaponRadio = new JRadioButton("Weapon");

		//int that keeps track of what type of item is being created
		static int typeSelection = 1;

		//the int that tells what inventory slot to add the item to
		static int  inventoryslot = 0;

		//the string that holds the name of the item being created
		static String inventoryname;

		//the string that holds the type of the item being created if needed
		static String inventoryclass;

		//the string that holds the value of the item being created if needed
		static String inventorynumber;

		//the string that is what file to write to and the file object to be the fill
		static String file = "no file selected";
		static File userFile;

		//the text fields having to do with name, race, class, level, and allignment
		public static TextField nameField = new TextField();
		public static TextField raceField = new TextField();
		public static TextField classField = new TextField();
		public static TextField levelField = new TextField();
		public static TextField allignmentField = new TextField();

		//the text fields having to do with the slot to add the item to, the item name, the item type and the value for item stats
		public static TextField spotField = new TextField();
		public static TextField itemNameField = new TextField();
		public static TextField typeField = new TextField();
		public static TextField valueField = new TextField();

		//the labels for the text fields
		public JLabel nameLabel = new JLabel("|        Name");
		public JLabel raceLabel = new JLabel("|        Race");
		public JLabel classLabel= new JLabel("|        Class");
		public JLabel levelLabel = new JLabel("|       Level");
		public JLabel allignmentLabel = new JLabel("|     Allignment");

		//the label for the panel that shows what error is occuring
		public static JLabel errorLabel = new JLabel("This is where errors appear");

		//the buttons to reroll stats, add an item to the inventory, and the button to save the character
		public JButton rerollButton = new JButton("Reroll Stats");
		public JButton itemButton = new JButton("Add Item");
		public JButton saveButton = new JButton("Save Character");


	// the listener and constructor for the reroll event
	RollListener rollPress = new RollListener();

	public class RollListener implements ActionListener
		{
			public void actionPerformed(ActionEvent event)
				{

					rollStats(0);
				}
		}

	//the method that rerolls the stats and sets the labels to be the value of the stat
	public static void rollStats(int rollnumber)
		{
			if(rollnumber >= 6)
			{
				System.out.println("Your stats have been rolled");
			}

			else
			{
				currentstat = roll.nextInt(20)+1;
				statsInt[rollnumber] = currentstat;
				rollStats(rollnumber + 1);
			}


			stat1.setText(Integer.toString(statsInt[0]));
			stat2.setText(Integer.toString(statsInt[1]));
			stat3.setText(Integer.toString(statsInt[2]));
			stat4.setText(Integer.toString(statsInt[3]));
			stat5.setText(Integer.toString(statsInt[4]));
			stat6.setText(Integer.toString(statsInt[5]));



		}

	// the listener and constructor for the radio buttons to select what kind of item is being created
	TypeListener typePress = new TypeListener();

	public class TypeListener implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			if (itemRadio.isSelected())
			{
				typeSelection = 1;
				typeField.setEditable(false);
				valueField.setEditable(false);
			}

			if (armorRadio.isSelected())
			{
				typeSelection = 2;
				typeField.setEditable(true);
				valueField.setEditable(true);
			}

			if (weaponRadio.isSelected())
			{
				typeSelection = 3;
				typeField.setEditable(true);
				valueField.setEditable(true);
			}
		}
	}


	// the listener and constructor for the event to add items to the inventory
	AddListener addPress = new AddListener();

	public class AddListener implements ActionListener
		{
			public void actionPerformed(ActionEvent event)
				{



					if(spotField.getText().equals(""))
					{
						errorLabel.setText("There must be a value between 1-20 in the slot field");
					}

					else
					{

						try
								{

						if(Integer.parseInt(spotField.getText()) < 1 || Integer.parseInt(spotField.getText()) > 10)
						{
							errorLabel.setText("Item slot must be 1 - 10");
							throw new invalidInventoryException();
						}

						else
						{
						inventoryslot = Integer.parseInt(spotField.getText());
						createItem();
						errorLabel.setText("Item added");
						}

							}

						catch(invalidInventoryException e)
								{



								}


					}



				}
		}

	//the method that creates the item that will be added to the inventory
	public static void createItem()
		{

			if(typeSelection == 1)
			{
				inventoryname = itemNameField.getText();

				inventory[inventoryslot-1] = new item(inventoryname);
				invs[inventoryslot-1].setText(inventory[inventoryslot-1].toString());
				System.out.println(inventory[inventoryslot]);
			}

			if(typeSelection == 2)
			{
				inventoryname = itemNameField.getText();
				inventoryclass = typeField.getText();
				inventorynumber = valueField.getText();

				inventory[inventoryslot-1] = new armor(inventoryclass, inventoryname, inventorynumber);
				invs[inventoryslot-1].setText(inventory[inventoryslot-1].toString());
				System.out.println(inventory[inventoryslot-1]);
			}

			if(typeSelection == 3)
			{
				inventoryname = itemNameField.getText();
				inventoryclass = typeField.getText();
				inventorynumber = valueField.getText();

				inventory[inventoryslot-1] = new weapon(inventoryclass, inventoryname, inventorynumber);
				invs[inventoryslot-1].setText(inventory[inventoryslot-1].toString());
				System.out.println(inventory[inventoryslot-1]);
			}
	}


	// the listener and constructor for the event to save the character and check if all of the top fields are filled
	SaveListener savePress = new SaveListener();

	public class SaveListener implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{


			name = nameField.getText();
			if(nameField.getText().equals(""))
			{
				nameField.setText("Name Required");
			}


			race = raceField.getText();
			if(raceField.getText().equals(""))
			{
				raceField.setText("Race Required");
			}


			classes = classField.getText();
			if(classField.getText().equals(""))
			{
				classField.setText("Class Required");
			}


			try
			{

				levelString = levelField.getText();
				level = Integer.parseInt(levelString);
			}

			catch(Exception anException)
			{
				levelField.setText("Level must be 1-20");
			}

			if(levelField.getText().equals(""))
			{
				levelField.setText("Level Required");
			}




			try{

			if(level < 1 || level > 20)
			{
				throw new invalidLevelException();
			}

				}

			catch(invalidLevelException e)
			{
								levelField.setText("Level must be 1 - 20");

			}

			allignment = allignmentField.getText();
			if(allignmentField.getText().equals(""))
			{
				allignmentField.setText("Allignment Required");
			}


			if(nameField.getText().equals("Name Required") || raceField.getText().equals("Race Required") || classField.getText().equals("Class Required") || levelField.getText().equals("Level must be 1-20") || allignmentField.getText().equals("Allignment Required"))
			{
				errorLabel.setText("Some fields are not filled");
			}
			else
			{
				savecharacter();
				errorLabel.setText("All areas filled");
			}


		}
	}



// the method that saves the character
	public static void savecharacter()
		{
 			file = "Character.txt";
			File characterfile;
			characterfile = new File(file);
			try
				{
					BufferedReader filereader = new BufferedReader(new FileReader(characterfile));
					BufferedWriter filewriter = new BufferedWriter(new FileWriter(characterfile));

					Scanner filescan;
					String fileline = "";
					fileline = filereader.readLine();




					if(fileline == null)
						{
							filewriter.write(name + ", " + race + ", " + classes + ", " + level + ", "  + allignment);
							filewriter.newLine();
							filewriter.write("Stats");
							filewriter.newLine();
							filewriter.write("Strength " + statsInt[0]);
							filewriter.newLine();
							filewriter.write("Dexterity " +  statsInt[1]);
							filewriter.newLine();
							filewriter.write("Constitution " + statsInt[2]);
							filewriter.newLine();
							filewriter.write("Intelligence " + statsInt[3]);
							filewriter.newLine();
							filewriter.write("Wisdom " + statsInt[4]);
							filewriter.newLine();
							filewriter.write("Charisma " + statsInt[5]);
							filewriter.newLine();
							filewriter.write("Inventory");
							filewriter.newLine();
							filewriter.write("1: " + inventory[0]);
							filewriter.newLine();
							filewriter.write("2: " + inventory[1]);
							filewriter.newLine();
							filewriter.write("3: " + inventory[2]);
							filewriter.newLine();
							filewriter.write("4: " + inventory[3]);
							filewriter.newLine();
							filewriter.write("5: " + inventory[4]);
							filewriter.newLine();
							filewriter.write("6: " + inventory[5]);
							filewriter.newLine();
							filewriter.write("7: " + inventory[6]);
							filewriter.newLine();
							filewriter.write("8: " + inventory[7]);
							filewriter.newLine();
							filewriter.write("9: " + inventory[8]);
							filewriter.newLine();
							filewriter.write("10: " + inventory[9]);
							filewriter.newLine();

						}

							filereader.close();
							filewriter.close();

							}
					catch(Exception anException)
					{
						errorLabel.setText("Error reading file");
					}
		}


		//blank exception if the level int is not between or including 1-20
		public class invalidLevelException extends RuntimeException
		{



		}

		//blank exception if the inventoryslot int is not between or including 1-10
		public class invalidInventoryException extends RuntimeException
		{



		}




		//the actual panel and adding things to it
		public NewFinalPanel()
		{

			//loop sso the blank invenotry slots save as nothing instead of null
			for(int i = 0; i < inventory.length; i++)
			{
				inventory[i] = new item("nothing");
			}


			//adding the listeners to their respective buttons
			rerollButton.addActionListener(rollPress);
			itemButton.addActionListener(addPress);
			saveButton.addActionListener(savePress);

			//making the button group and adding the radio buttons to that group
			ButtonGroup itemGroup = new ButtonGroup();
			itemGroup.add(itemRadio);
			itemGroup.add(armorRadio);
			itemGroup.add(weaponRadio);

			//adding the listener to each of the radio buttons
			itemRadio.addActionListener(typePress);
			armorRadio.addActionListener(typePress);
			weaponRadio.addActionListener(typePress);



			//setting the layout of the main panel
			setLayout(new BorderLayout());


			//setting the layout of the subpanels
			JPanel namePanel = new JPanel();
			namePanel.setLayout(new GridLayout(1,10));

			JPanel statPanel = new JPanel();
			statPanel.setLayout(new GridLayout(7,2));

			JPanel inventoryPanel = new JPanel();
			inventoryPanel.setLayout(new GridLayout(11,1));

			JPanel itemPanel = new JPanel();
			itemPanel.setLayout(new GridLayout(13,1));

			JPanel savePanel = new JPanel();
			savePanel.setLayout(new GridLayout(2,1));


			// label for the inventory
			JLabel inventoryLabel = new JLabel("Inventory");

			//labels for the add item panel
			JLabel itemLabel = new JLabel("Use this menu to add items");
			JLabel nothingLabel = new JLabel("nothing");
			JLabel spotLabel = new JLabel("What slot to add item");
			JLabel itemNameLabel = new JLabel("Name of Item");
			JLabel typeLabel = new JLabel("Item Type");
			JLabel valueLabel = new JLabel("Attack/Defense");


			//labels fo the stat panel that show what numer represents what value
			JLabel statLabel = new JLabel("Stats");
			JLabel strengthLabel = new JLabel("Strength");
			JLabel dexterityLabel = new JLabel("Dexerity");
			JLabel constitutionLabel = new JLabel("Constitution");
			JLabel intelligenceLabel = new JLabel("Intelligence");
			JLabel wisdomLabel = new JLabel("Wisdom");
			JLabel charismaLabel = new JLabel("Charisma");


			//adding the sub panels to the main panel
			add(namePanel, BorderLayout.PAGE_START);
			add(statPanel, BorderLayout.LINE_START);
			add(inventoryPanel, BorderLayout.CENTER);
			add(itemPanel, BorderLayout.LINE_END);
			add(savePanel, BorderLayout.PAGE_END);


			//adding the text fields and labels to the name panel
			namePanel.add(nameLabel);
			namePanel.add(nameField);
			namePanel.add(raceLabel);
			namePanel.add(raceField);
			namePanel.add(classLabel);
			namePanel.add(classField);
			namePanel.add(levelLabel);
			namePanel.add(levelField);
			namePanel.add(allignmentLabel);
			namePanel.add(allignmentField);

			//adding the text fields and labels to the stat panel
			statPanel.add(statLabel);
			statPanel.add(rerollButton);
			statPanel.add(strengthLabel);
			statPanel.add(stat1);
			statPanel.add(dexterityLabel);
			statPanel.add(stat2);
			statPanel.add(constitutionLabel);
			statPanel.add(stat3);
			statPanel.add(intelligenceLabel);
			statPanel.add(stat4);
			statPanel.add(wisdomLabel);
			statPanel.add(stat5);
			statPanel.add(charismaLabel);
			statPanel.add(stat6);


			//adding the labels to the inventory label
			inventoryPanel.add(inventoryLabel);
			inventoryPanel.add(invs[0]);
			inventoryPanel.add(invs[1]);
			inventoryPanel.add(invs[2]);
			inventoryPanel.add(invs[3]);
			inventoryPanel.add(invs[4]);
			inventoryPanel.add(invs[5]);
			inventoryPanel.add(invs[6]);
			inventoryPanel.add(invs[7]);
			inventoryPanel.add(invs[8]);
			inventoryPanel.add(invs[9]);

			//adiing the labels, text fields and buttons to the add item panel
			itemPanel.add(itemLabel);

			itemPanel.add(itemRadio);
			itemPanel.add(armorRadio);
			itemPanel.add(weaponRadio);

			itemPanel.add(spotLabel);
			itemPanel.add(spotField);

			itemPanel.add(itemNameLabel);
			itemPanel.add(itemNameField);

			itemPanel.add(typeLabel);
			itemPanel.add(typeField);

			itemPanel.add(valueLabel);
			itemPanel.add(valueField);

			itemPanel.add(itemButton);


			//adding the button and label to the save panel
			savePanel.add(saveButton);
			savePanel.add(errorLabel);

		}



			//the main to create the panel
			public static void main(String[]args)
			{
				JFrame sheetFrame = new JFrame("Character Creator");
				sheetFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


				sheetFrame.add(new NewFinalPanel());
				sheetFrame.setSize(1200,600);
				sheetFrame.setVisible(true);
			}

}