import java.util.Scanner;
import java.util.Random;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.Arrays;


public class NewFinal
{

			static int[] stats = new int[6];
			static int currentstat;
			static Random roll = new Random();
	public static void main(String [] args)
	{
			Scanner Option = new Scanner(System.in);
			int Choice;

			Scanner nameOption = new Scanner(System.in);
			String name = "none chossen";

			Scanner raceOption = new Scanner(System.in);
			String race = "none chossen";

			Scanner levelOption = new Scanner(System.in);
			int level = 0;

			item[] inventory = new item[10];

			Scanner inventoryOption = new Scanner(System.in);
			int  inventoryslot = 0;
			int  inventorytype;
			String inventoryname;
			int inventorynumber;
			String inventoryclass;



			Scanner fileOption = new Scanner(System.in);
			String file = "no file selected";
			File userFile;
			String fileanswer;
			char fileSelect = 'N';

			Scanner textOption = new Scanner(System.in);
			String text = "";
			String writeAnswer;
			char textSelect = 'N';

			Scanner quitOption = new Scanner(System.in);
			String quit;
			char quitSelect = 'N';

			for(int spot = 0; spot < inventory.length; spot++)
			inventory[spot] = new item("nothing");

			String[] statisticName ={"Strength ","Dexterity ","Constitution ","Intelligence ","Wisdom ","Charisma "};



			while (quitSelect =='N')
			{
					System.out.println("To select a task type the number next to the option.");
					System.out.println("1.	Set name of character. " + name);
					System.out.println("2.	Set race of character " + race);
					System.out.println("3.	Roll your stats");
					System.out.println("4.	Show stats");
					System.out.println("5.	Set level of character " + level);
					System.out.println("6.	Show inventory.");
					System.out.println("7.	Change inventory.");
					System.out.println("8	Save character.");



					//choose an option
					Choice = Option.nextInt();

					//verification of input for the menu
					if( Choice != 1 && Choice != 2 && Choice != 3 && Choice != 4 && Choice != 4  && Choice != 5 && Choice != 6 && Choice != 7&& Choice != 8)
					{
					System.out.println("Please enter a correct value\n");
					Choice = Option.nextInt();
					}

					switch(Choice)
					{
						case 1 :

						System.out.println("What name will you have?");
						name = nameOption.next();

						break;

						case 2 :

						System.out.println("What race will you be?");
						race = raceOption.next();
						break;

						case 3 :
						rollStats(0);
						break;

						case 4 :
						System.out.println("");
						for(int stat = 0; stat < stats.length; stat++)
						System.out.println(statisticName[stat] + stats[stat]);
						System.out.println("");

						break;

						case 5 :

						System.out.println("What level are you?");
						level = levelOption.nextInt();
						break;

						case 6 :

						for(int spot = 0; spot < inventory.length; spot++)
						System.out.println((spot+1) +": " + inventory[spot]);
						break;

						case 7 :

						System.out.println("What inventory slot would you like to edit");
						inventoryslot = inventoryOption.nextInt();
						System.out.println("What type of item do you want to add");
						System.out.println("1: An item");
						System.out.println("2: An armor");
						System.out.println("3: A weapon");
						inventorytype = inventoryOption.nextInt();
						switch(inventorytype)
						{
							case 1 :
						System.out.println("What is the name of the item");
						inventoryname = inventoryOption.next();
						inventory[inventoryslot - 1] = new item(inventoryname);

						break;

							case 2 :
						System.out.println("What is the name of the armor");
						inventoryname = inventoryOption.next();
						System.out.println("What type of armor is it");
						inventoryclass = inventoryOption.next();
						System.out.println("What is the defense of the armor");
						inventorynumber = inventoryOption.nextInt();
						inventory[inventoryslot - 1] = new armor(inventoryclass,inventoryname,inventorynumber);

						break;

						case 3 :
						System.out.println("What is the name of the weapon");
						inventoryname = inventoryOption.next();
						System.out.println("What type of weapon is it");
						inventoryclass = inventoryOption.next();
						System.out.println("What is the damage of the weapon");
						inventorynumber = inventoryOption.nextInt();
						inventory[inventoryslot - 1] = new weapon(inventoryclass,inventoryname,inventorynumber);
						break;

						}

						break;

						case 8:
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
									filewriter.write(name + " \n" + race + " \n" + level + " \n"  + inventory[0]);
									filewriter.newLine();
									//filewriter.write(name + " \n" + race + " \n" + level + " \n"  + inventory[0]);
										//filewriter.write(inventory[0]);
										//filewriter.newLine();

								}

								//if(fileline == null)
								//{
								//for(int space = 0; space < inventory.length; space++)
								//{
								//	filewriter.write(inventory[0]);
								//	filewriter.newLine();
								//}
								//}
									filereader.close();
									filewriter.close();

								}
								catch(Exception anException)
								{
								System.out.println("Error reading file");
								}
								break;


							}//end pf switch
			}// end of while quit = n
	}//end of main


public static void rollStats(int rollnumber)
	{
		if(rollnumber >= 6)
		{
			System.out.println("Your stats have been rolled");
		}

		else
		{
		currentstat = roll.nextInt(20)+1;
		stats[rollnumber] = currentstat;
		rollStats(rollnumber + 1);

		}
	}


}//end of class