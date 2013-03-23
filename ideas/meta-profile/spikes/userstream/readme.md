# User Stream
How can we best agregate a range of sources of updates for a given user's online identiy?

## Background
This service is designed to create a unified list of activities which a given user has taken part in. This will allow them to create a sort of "meta-profile" which shows updates from the user around the web. These "meta-profiles" can then talk to each other to form a distributed social network. This network can then be used as the basis for a universal internet profile. 

This spike solution is to investigate the possiblity of using *already existing* technolgies to obtain infomation about new goings on from a given user.

## 'Pull' Based methods
Assuming the services we want to interact with either a) don't care about the service or b) don't know about the service how can we get updates but does have a public way of asking, "have their been any updates?" we can use the public API to extract the data we want for our meta-profile.

BE CAREFUL! some services treat the user's data as their property rather than the users. It *might* be seen as terms of use voilation to take this data and publish it on the web somewhere else (even at the users request). Please check the TOS before using such techiques to build profiles.

### How can we support the maximum number of sources easily?
Easy! there is already a protocol for this... it's called RSS :D. We can agregate RSS feeds of user activties when the sites provide them. We can use cool tricks like last modified headers to save us fetching updates we already know about and we can put the update fetcher in a cron job to do it periodiclly and fetch the updates.

## Complex structure and Data
Where RSS is not detailed enuph, not provided or not suitable to mine updates from given sources there are a number of other approches which can be used.

### Scraping
Scraping is when you take the HTML of a page and extract data from it. This approch is very brittle but will work even when there is no public API provided that you can access the site. Most sits will not like this solution.

### Public API endpoints
Where sites provide the ability to use a publiclly available API, the API can be used to query for updates from the user. This approch requries a dedicated script to be written for the service which is time consuming. This approch allows for much richer data to be provided than the RSS approch.

### 'Unoffical APIs'
It might be possible to misuse other infomation provided by a website (eg newsletter emails, private AJAX APIs, files accidently made public on the web, etc...) to build a picture of updates. It's quite easy to see why this is probably a *very bad idea*. Giving a web service access to your emails is a majour privacy problem and the other examples are slightly mallicous. So I probably am not going to look at this one too closely ;).

## 'Push' based methods
The most bandwidth and processing friendly approch is to have the service in question tell us when something has happend. This requires the services to be capable of talking to us and letting us know that something has happened.

* How can we make sure the data is not spoofed
* Is there already a protocol out there for this? (OStatus? Open Soical?)
* How realistic is it to assume web services will be able to let us know when something happens?
** Not very, as this is decenteralised they would need a mapping of lots of users=>endpoints
** Bandwidth and their processing time
** Can we make the client's browser do this? (privacy issues, legal issues, etc...)

