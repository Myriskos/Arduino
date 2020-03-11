void loop(){

String readString = "%Enter%your%string%here";

// Split the readString by a pre-defined delimiter in a simple way. '%'(percentage) is defined as the delimiter in this project.
int delimiter, delimiter_1, delimiter_2, delimiter_3;
delimiter = readString.indexOf("%");
delimiter_1 = readString.indexOf("%", delimiter + 1);
delimiter_2 = readString.indexOf("%", delimiter_1 +1);
delimiter_3 = readString.indexOf("%", delimiter_2 +1);

// Define variables to be executed on the code later by collecting information from the readString as substrings.
String first = readString.substring(delimiter + 1, delimiter_1);
String second = readString.substring(delimiter_1 + 1, delimiter_2);
String third = readString.substring(delimiter_2 + 1, delimiter_3);

}
