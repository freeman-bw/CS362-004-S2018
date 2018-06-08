


import java.util.Scanner;
import junit.framework.TestCase;
import java.util.concurrent.ThreadLocalRandom;

/* CS362 Final Project Part B
 * 
 * Authors: Ankita Mistry, Brent Freeman
 * 
 * These test functionsare used to test the Apache Commons UrlValidator functions.
 * Tests include manual, partition
 * 
 * 
 *
 * */
 

public class UrlValidatorTest extends TestCase {
	
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   String[] slashArr = {"://"};
   
   
   String[] myGoodURLs = {"http://www.google.com", "http://google.com","http://www.cnn.com", "http://www.oregonlive.com", "http://www.oregonstate.edu", "http://www.wired.com",
		   "http://www.portlandoregon.gov", "https://www.wikipedia.org", "http://www.nasa.gov"};
   
   String[] myBadURLs = {"http://ww.google.com", "http://www.google.o", "http://www.com", "http://www.google..com", ""};
   

   public void testManualTest()
   {

	   System.out.println("Manual testing of known good and known bad urls");

	  // This is an option to perform manual testing based on user input
	   
	   /* 
	   System.out.println("Enter a test URL: ");
	   Scanner scanner = new Scanner(System.in);
	   String userURL = scanner.nextLine();	   
	   
	       UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	       if (urlValidator.isValid(userURL)) {
	          System.out.println(userURL + ": url is valid");
	       } else {
	          System.out.println(userURL + ": url is invalid");
	       }
	       
	           UrlValidator urlValidator1 = new UrlValidator();
	           if (urlValidator1.isValid(userURL)) {
	              System.out.println(userURL + ": url is valid");
	           } else {
	              System.out.println(userURL + ": url is invalid");
	       }
	       */
	   
	   

	   //UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   UrlValidator urlValidator = new UrlValidator();

	   System.out.println("Begin good urls");
	   //test good urls
	   for (int x = 0; x < myGoodURLs.length; x++) {
		   if (urlValidator.isValid(myGoodURLs[x])) {
			   System.out.println(myGoodURLs[x] + ": url is valid");
		   } else {
			   System.out.println(myGoodURLs[x] + ": url is invalid");
		   }

	   }

	   System.out.println("Begin bad urls");
	   //test bad urls
	   for (int x = 0; x < myBadURLs.length; x++) {
		   if (urlValidator.isValid(myBadURLs[x])) {
			   System.out.println(myBadURLs[x] + ": url is valid");
		   } else {
			   System.out.println(myBadURLs[x] + ": url is invalid");
		   }
	   }

	   System.out.println("End Manual testing");

   }
	   

public void testYourFirstPartition() //Ankita's test
   { 
	   //You can use this function to implement your First Partition testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] pathregex = {"@","&","?","=","+",",",".","!","/","~","*","'","%","$","_",";"};
	   String TestString;
	   
	   System.out.print("testYourFirstPartition entry\n");
	   
	   //
	   // Test if path section of the URL excepts all the regular expressions
       //
	   for(int i = 0; i < pathregex.length; i++) {
		   TestString = "http://www.google.com/forum" + pathregex[i] + "questions" + pathregex[i];
		   //System.out.print(TestString + "\n");
		   if (urlVal.isValid(TestString) == false) {
			   System.out.printf("    Test failed: the URL path does not except %s character\n", pathregex[i]);
		   }
	   }
	   
	   System.out.print("testYourFirstPartition exit\n\n");
	   
   }
   
String[] badPath = { "ttps", "htts", "ftp", "htp", "htt", "ttp", "HTT", "FT", "local", "localhost"};
String[] goodPath = { "http", "HTTP", "https", "HTTPS", "ftp", "FTP"};

   public void testYourSecondPartition(){
		 //This section partitions the differen path schemes and tests them via the isValidScheme method.  
	   
	  System.out.println("Testing path schemes");
	  
	   String[] schemes = {"http","https"};
	   //UrlValidator urlVal = new UrlValidator(schemes);
	   //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   UrlValidator urlVal = new UrlValidator();
	   
	   for (int x = 0; x < goodPath.length; x++) {
		   if (urlVal.isValidScheme(goodPath[x])) {
			   System.out.println(goodPath[x] + ": url is valid");
		   } else {
			   System.out.println(goodPath[x] + ": url is invalid");
		   }
	   }
	   
	   for (int x = 0; x < badPath.length; x++) {
		   if (urlVal.isValidScheme(badPath[x])) {
			   System.out.println(badPath[x] + ": url is valid");
		   } else {
			   System.out.println(badPath[x] + ": url is invalid");
		   }
	   }

   }
   //You need to create more test cases for your Partitions if you need to 
   
   String[] pre = {"www", "ww3", ""};
   String[] urls = {"google", "facebook", "cnn", "npr", "dogs", "oregonstate"};
   String[] domains = {"com", "org", "net", "co", "ddd", "jp", "edu"};
   String[] allSlash = {"://", "//:", ":/", "//"};
   String[] allPaths = { "ttps", "htts", "ftp", "htp", "htt", "ttp", "HTT", "FT", "local", "localhost", "http", "HTTP", "https", "HTTPS", "ftp", "FTP"};
   String[] pathregex = {"@","&","?","=","+",",",".","!","/","~","*","'","%","$","_",";", ""};
   
public void testIsValid()
   {
	//this section creates a random string from different path parts, concatenates them together and tests if it is valid, printing out the results
	
	System.out.println("\nBegin Testing Randomly Created Paths");
	
	 //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	UrlValidator urlVal = new UrlValidator();
	
	for (int x = 0; x < 100; x++) {
		
		int randomPre = ThreadLocalRandom.current().nextInt(0, pre.length );
		int randomUrls = ThreadLocalRandom.current().nextInt(0, urls.length );
		int randomDomains = ThreadLocalRandom.current().nextInt(0, domains.length );
		int randomAllSlash = ThreadLocalRandom.current().nextInt(0, allSlash.length);
		int randomAllPaths = ThreadLocalRandom.current().nextInt(0, allPaths.length);
		int randomRegex = ThreadLocalRandom.current().nextInt(0, pathregex.length);
		
		String testPath = allPaths[randomAllPaths] + allSlash[randomAllSlash] + pre[randomPre] + "." + urls[randomUrls]+ "."+ domains[randomDomains]+pathregex[randomRegex];
		   
		
		   if (urlVal.isValid(testPath)) {
			   System.out.println(testPath + ":Pass");
		   } else {
			   System.out.println(testPath + ": Fail");
		   }
	   }
	
	System.out.println("\nEnd Testing Randomly Created Paths");
	
   }
   
}
