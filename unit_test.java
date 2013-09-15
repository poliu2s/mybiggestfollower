package com.example.tests;

import com.thoughtworks.selenium.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;
import java.util.regex.Pattern;

public class unit2 {
	private Selenium selenium;

	@Before
	public void setUp() throws Exception {
		selenium = new DefaultSelenium("localhost", 4444, "*chrome", "http://mybiggestfollower-pomart.rhcloud.com/");
		selenium.start();
	}

	@Test
	public void testUnit2() throws Exception {
		selenium.open("/connect.php");
		selenium.click("link=Sign in with Twitter");
		selenium.waitForPageToLoad("30000");
		assertEquals("Twitter / Authorize an application", selenium.getTitle());
		selenium.click("id=allow");
		selenium.waitForPageToLoad("30000");
		assertEquals("Sign out", selenium.getText("link=Sign out"));
		verifyEquals("1 follower bubbles for user po_rpi :", selenium.getText("css=div.row-fluid.marketing > h3"));
		verifyEquals("Update data", selenium.getText("link=Update data"));
		selenium.click("link=Update data");
		selenium.waitForPageToLoad("30000");
		verifyEquals("Contact", selenium.getText("link=Contact"));
		verifyEquals("Po Liu", selenium.getText("link=Po Liu"));
		selenium.click("link=Sign out");
		selenium.waitForPageToLoad("30000");
		assertEquals("Sign in with Twitter", selenium.getText("link=Sign in with Twitter"));
	}

	@After
	public void tearDown() throws Exception {
		selenium.stop();
	}
}
