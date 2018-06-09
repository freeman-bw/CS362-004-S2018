import java.util.Scanner;
import junit.framework.TestCase;
import java.util.concurrent.ThreadLocalRandom;

/* CS362 Final Project Part B
 * 
 * Authors: Ankita Mistry, Brent Freeman
 * 
 * These test functionsare used to test the Apache Commons UrlValidator functions.
 * Tests include manual (two different tests available), partition(scheme regex), partition(scheme path), and random path
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

	 //You can use this function to implement your manual testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.print("testManualTest entry\n");

	   //
	   // Test URL with <Scheme><Authority><Path><Query><Fragment> components
       //
	   if (urlVal.isValid("http://www.google.com/forum/questions/?tag=networking&order=newest#top") == false) {
		   System.out.print("    Test failed with <Scheme><Authority><Path><Query><Fragment> components\n");
	   } else {
		   System.out.print("    Test passed with <Scheme><Authority><Path><Query><Fragment> components\n");
	   }

	   //
	   // Test URL with <Scheme><Authority><Path><Query> components
       //
	   if (urlVal.isValid("http://www.google.com/forum/questions/?tag=networking&order=newest") == false) {
		   System.out.print("    Test failed with <Scheme><Authority><Path><Query> components\n");
	   } else {
		   System.out.print("    Test passed with <Scheme><Authority><Path><Query> components\n");
	   }

	   //
	   // Test URL with <Scheme><Authority><Path> components
       //
	   if (urlVal.isValid("http://www.google.com/forum/questions/") == false) {
		   System.out.print("    Test failed with <Scheme><Authority><Path> components\n");
	   } else {
		   System.out.print("    Test passed with <Scheme><Authority><Path> components\n");
	   }

	   //
	   // Test URL with <Scheme><Authority> components
       //
	   if (urlVal.isValid("http://www.google.com") == false) {
		   System.out.print("    Test failed with <Scheme><Authority> components\n");
	   } else {
		   System.out.print("    Test passed with <Scheme><Authority> components\n");
	   }
	   
	   System.out.print("testManualTest exit\n\n");
	   
	   
	   //Alternative manual test function (duplicate efforts by team members):
	   
	   /*
	   System.out.println("Manual testing of known good and known bad urls");

	  // This is an option to perform manual testing based on user input
	   
	  // /
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
	      // 
	   
	   

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
*/
   }
	   

   public void testYourFirstPartition()
   {

	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	      
	   // Scheme regex is defined as such: 
	   //    ^\\p{Alpha}[\\p{Alnum}\\+\\-\\.]*
	   //   |-|---------|--------------------|
	   //    1     2             3
	   //   1: must be new line beginning
	   //   2: first character must be a alphabet
	   //   3: rest of the characters can be alpha numeric
       //
	   ResultPair[] testSchemeRegex = {new ResultPair("http://", true),    // Instance is inverting the flag
			   															   // root caused by comparing the passing vs. failing results
			   															   // using debugger to check the initial state of the flag.               						  
			   						   // new ResultPair("HTTP://", true),  // program crashed with this input
            						   new ResultPair("h@tp://", false),
            						   new ResultPair("1ttp://", false),
            						   //new ResultPair("ht3p://", true),  // program crashed with this input
            						   new ResultPair("1234://", false),
            						   //new ResultPair("h://", true),     // program crashed with this input
            						   //new ResultPair("h1://", true)     // program crashed with this input
            						   };
	   
	   //
	   // Authority regex is defined as such: 
	   //   (?:\\[([0-9a-fA-F:]+)\\]|(?:(?:[a-zA-Z0-9%-._~!$&'()*+,;=]+(?::[a-zA-Z0-9%-._~!$&'()*+,;=]*)?@)?([\\p{Alnum}\\-\\.]*)))(?::(\\d*))?(.*)?
	   //   |----------------------------------------------------------------------------------------------|------------------|----------------|--|
	   //    							1          																	2                3           4
	   //   1,2,3: ignore groupings
	   //   4: any characters
	   //
	   ResultPair[] testAuthRegex = {new ResultPair("www.google.com", true),
				   					new ResultPair("1234.google.com", true),
				   					new ResultPair("www.google.1234", false),
				   					new ResultPair("www.1234.com", true),
				   					new ResultPair("www.1234.com12", false),
				   					new ResultPair("1235.4567.890", false),
				   					new ResultPair("www.goo+gle.com", false),
				   					new ResultPair("255.255.255.255", true),
	                                new ResultPair("256.256.256.256", false)
	                                };
	   //
	   // Port requirements:
	   // 1: must be a number
	   // 2: must be between zero & 65535
	   //
	   ResultPair[] testPortRegex = {new ResultPair(":1234", true),
									new ResultPair(":ab", false),
									new ResultPair(":", true),
									new ResultPair(":@", false),
									new ResultPair(":65536", false),
									new ResultPair(":-1", false)
									};   
	   
	   //
	   // Query regex is defined as such:
	   //   ^(\\S*)
	   //  |-|----|
	   //   1   2
	   // 1: must be new line beginning
	   // 2: Test for any non-whitespace character
	   //
	   ResultPair[] testQueryRegex = {new ResultPair("?abcd", true),
									new ResultPair("?a bcd", false),
									new ResultPair("? abcd", false),
									new ResultPair("?@bcd", true),
									new ResultPair("?1234", true),
									new ResultPair("?a2bcd", true)
									}; 
	   
	   //
	   // Path regex is defined as such:
	   //  [-\\w:@&?=+,.!/~*'%$_;\\(\\)]*)?$
	   //  |-----|-----------------------|
	   //     1           2
	   // 1: A word character a-z, A-Z, 0-9
	   // 2. A special character @&?=+,.!/~*'%$_;\\(\\)
	   //
	   String[] testPathRegex = {"@","&","?","=","+",",",".","!","/","~","*","'","%","$","_",";"};
	   String TestString;
	   ResultPair testPair;
	   
	   System.out.print("testYourFirstPartition entry\n");

	   //
	   // Test the <scheme> component regex violation
	   //
	   for(int i = 0; i< testSchemeRegex.length; i++) {
		   	testPair = testSchemeRegex[i];
		   	TestString = testPair.item + "www.google.com";
	   		if (urlVal.isValid(TestString) != testPair.valid ) {
	   			System.out.print("    <Scheme> partition test failed with " + TestString + "\n");
	   		} else {
	   			System.out.print("    <Scheme> partition test passed with " + TestString + "\n");
	   		}
	   }
	   System.out.print("\n");
	   
	   //
	   // Test the <authority> component regex violation
	   //
	   for(int i = 0; i< testAuthRegex.length; i++) {
		   	testPair = testAuthRegex[i];
		   	TestString = "http://" + testPair.item;
	   		if (urlVal.isValid(TestString) != testPair.valid ) {
	   			System.out.print("    <Authority> partition test failed with " + TestString + "\n");
	   		} else {
	   			System.out.print("    <Authority> partition test passed with " + TestString + "\n");
	   		}
	   }
	   System.out.print("\n");
	   
	   //
	   // Test the <port> component regex violation
	   //
	   for(int i = 0; i< testPortRegex.length; i++) {
		   	testPair = testPortRegex[i];
		   	TestString = "http://www.google.com" + testPair.item;
	   		if (urlVal.isValid(TestString) != testPair.valid ) {
	   			System.out.print("    <Port> partition test failed with " + TestString + "\n");
	   		} else {
	   			System.out.print("    <Port> partition test passed with " + TestString + "\n");
	   		}
	   }
	   System.out.print("\n");

	   //
	   // Test the <path> component regex violation
	   //
	   for(int i = 0; i< testPathRegex.length; i++) {
		    TestString = "http://www.google.com.com/forum"  + testPathRegex[i] + "questions";
	   		if (urlVal.isValid(TestString) == false) {
	   			System.out.print("    <Path> partition failed with " + TestString +"\n");
	   		} else {
	   			System.out.print("    <Path> partition passed with " + TestString + "\n");
	   		}
	   }
	   System.out.print("\n");

	   //
	   // Test the <query> component regex violation
	   //
	   for(int i = 0; i< testQueryRegex.length; i++) {
		   testPair = testQueryRegex[i];
		   TestString = "http://www.google.com.com/forum,questions"+ testPair.item;
		   if (urlVal.isValid(TestString) != testPair.valid ) {
			   System.out.print("    <Query> partition failed with " + TestString +"\n");
		   } else {
			   System.out.print("    <Query> partition passed with " + TestString + "\n");
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
