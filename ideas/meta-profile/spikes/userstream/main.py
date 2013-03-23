##
# TODO add support for etag/modified checking to prevent us wasting bandwidth
##

##
# ENDPOINT API
# function(params, endpoint_params)
#
# params = params for a given user
# endpoint_params = generic for all users
##


from sources import rss_feed

endpoints = {
	"reddit":{
		"name": "reddit",
		"provider": rss_feed,
		"url": "http://www.reddit.com/user/%%USERNAME%%.rss"
	},
	"identi.ca":{
		"name": "identi.ca",
		"provider": rss_feed,
		"url": "http://identi.ca/%%USERNAME%%/rss"
	},
	"twitter":{
		"name": "twitter",
		"provider": rss_feed,
		"url": "https://api.twitter.com/1/statuses/user_timeline.rss?screen_name=%%USERNAME%%"
	},
	"github":{
		"name": "github",
		"provider": rss_feed,
		"url": "https://github.com/%%USERNAME%%.atom"
	},
	"gitorious": {
		"name": "gitorious",
		"provider": rss_feed,
		"url": "https://gitorious.org/~%%USERNAME%%/feed.atom"
	},
		
}

accounts = (
	("reddit", "webpigeon"),
	("identi.ca", "webpigeon"),
	("twitter", "webpigeon"),
	("github", "webpigeon"),
	("gitorious", "webpigeon")
)

updates = {}
for account in accounts:
	# Call the function with the url as an argument
	print ("requesting updates from %s" % account[0])
	endpoint = endpoints[account[0]]

	items = endpoint["provider"](account, endpoint)
	updates[account[0]] = items

	print (" -> got %d items" % len(items) )

# print out the feed items for debugging reasons (these should be put in a database or something :P)
for (source, items) in updates.items():
	for update in items:
		print "%s\n%s on %s" % (update["title"], update["published"], source)
		print ""
