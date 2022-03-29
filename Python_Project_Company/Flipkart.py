from selenium import webdriver
from bs4 import BeautifulSoup as bs
import pandas as pd

driver = webdriver.Chrome(executable_path="chromedriver")
products = []
prices = []
driver.get("https://www.flipkart.com/laptops/pr?sid=6bo,b5g&otracker=categorytree")
#the whole source code of page (inspect element)
content = driver.page_source
# print(content)

parsed_content = bs(content, "html.parser")
for eachproduct in parsed_content.findAll("a", href=True, attrs={"class": "_1fQZEK"}):
    name = eachproduct.find("div", attrs={"class": "_4rR01T"})
    price = eachproduct.find("div", attrs={"class": "_30jeq3 _1_WHN1"})
    products.append(name.text)
    prices.append(price.text)
print(products)
print(prices)
df = pd.DataFrame({"Product": products, "Prices": prices})
df.to_excel("laptops.xlsx", index=False)