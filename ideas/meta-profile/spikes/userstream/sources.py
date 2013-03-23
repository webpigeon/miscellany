##
# Sources for updates
##

import feedparser

def rss_feed(params, endpoint):
	url = endpoint["url"].replace("%%USERNAME%%", params[1])

	feed = feedparser.parse(url)
	updates = []
	for item in feed["items"]:
		updates.append( {
			"title": item["title"],
			"summary": item["summary"],
			"published": item["published"] if "published" in item else None
		} )
	return updates
