#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
#include "simulation.h"

using namespace std;

int main(int argc, char* argv[]) {
	ifstream namelist;
	ifstream logfile;
	string userdir;
	string username;
	User_t* user = new User_t[MAX_USERS];
	unsigned int usernum = 0;
	string num_s;
	string info_s;
	string post_s;
	unsigned int num_tags;
	string user1, user2, command;
	unsigned int postid, commentid, trendn;
	string text;

	// check the number of arguments
	try {
		if (argc < 3) {
			ostringstream oStream;
			oStream << "Error: Wrong number of arguments!" << endl;
			oStream << "Usage: ./p2 <username> <logfile>" << endl;
			throw Exception_t(INVALID_ARGUMENT, oStream.str());
		}
	}
	catch (Exception_t& exception) {
		cout << exception.error_info;
		return 0;
	}

	namelist.open(argv[1]);
	logfile.open(argv[2]);

	// check whether the file is opened or not
	try {
		if (!namelist) {
			ostringstream oStream;
			oStream << "Error: Cannot open file " << argv[1] << '!' << endl;
			throw Exception_t(FILE_MISSING, oStream.str());
		}
	}
	catch (Exception_t& exception) {
		cout << exception.error_info;
		return 0;
	}

	// check whether it can be opened or not
	try {
		if (!logfile) {
			ostringstream oStream;
			oStream << "Error: Cannot open file " << argv[2] << '!' << endl;
			throw Exception_t(FILE_MISSING, oStream.str());
		}
	}
	catch (Exception_t& exception) {
		cout << exception.error_info;
		return 0;
	}

	// read userdirectory
	getline(namelist, userdir);

	// read usernames
	while (getline(namelist, username)) {

		// check the number of users has exceeded the maximal number of users
		try {
			if (usernum >= MAX_USERS) {
				ostringstream oStream;
				oStream << "Error: Too many users!" << endl;
				oStream << "Maximal number of users is " << MAX_USERS << '.' << endl;
				throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
			}
		}
		catch (Exception_t& exception) {
			cout << exception.error_info;
			return 0;
		}

		user[usernum].username = username;
		usernum++;
	}

	// read userinfo
	for (unsigned int i = 0; i < usernum; ++i) {
		ifstream user_info;
		string directory = userdir + '/' + user[i].username + '/' + "user_info";
		user_info.open(directory);

		// check whether the file is opened or not
		try {
			if (!user_info) {
				ostringstream oStream;
				oStream << "Error: Cannot open file " << directory << '!' << endl;
				throw Exception_t(FILE_MISSING, oStream.str());
			}
		}
		catch (Exception_t& exception) {
			cout << exception.error_info;
			return 0;
		}

		getline(user_info, num_s);
		stringstream ss;
		ss << num_s;
		ss >> user[i].num_posts; // convert string to unsigned int

		// check whether the number of posts exceeds the maximal number of posts
		try {
			if (user[i].num_posts > MAX_POSTS) {
				ostringstream oStream;
				oStream << "Error: Too many posts for user " << user[i].username << '!' << endl;
				oStream << "Maximal number of posts is " << MAX_POSTS << '.' << endl;
				throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
			}
		}
		catch (Exception_t& exception) {
			cout << exception.error_info;
			return 0;
		}

		getline(user_info, num_s);
		stringstream sss;
		sss << num_s;
		sss >> user[i].num_following; // convert string to unsigned int

		// check whether the number of following exceeds the maximal number of following
		try {
			if (user[i].num_following > MAX_FOLLOWING) {
				ostringstream oStream;
				oStream << "Error: Too many followings for user " << user[i].username << '!' << endl;
				oStream << "Maximal number of followings is " << MAX_FOLLOWING << '.' << endl;
				throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
			}
		}
		catch (Exception_t& exception) {
			cout << exception.error_info;
			return 0;
		}

		for (unsigned int j = 0; j < user[i].num_following; ++j) {
			getline(user_info, info_s);
			for (unsigned int q = 0; q < usernum; ++q) {
				if (info_s == user[q].username) {
					user[i].following[j] = &user[q];
					break;
				}

			}
		}
		getline(user_info, num_s);
		stringstream ssss;
		ssss << num_s;
		ssss >> user[i].num_followers; // convert string to unsigned int

		// check whether the number of follower exceeds the maximal number of follower
		try {
			if (user[i].num_followers > MAX_FOLLOWERS) {
				ostringstream oStream;
				oStream << "Error: Too many followers for user " << user[i].username << '!' << endl;
				oStream << "Maximal number of followers is " << MAX_FOLLOWERS << '.' << endl;
				throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
			}
		}
		catch (Exception_t& exception) {
			cout << exception.error_info;
			return 0;
		}

		for (unsigned int j = 0; j < user[i].num_followers; ++j) {
			getline(user_info, info_s);
			for (unsigned int q = 0; q < usernum; ++q) {
				if (info_s == user[q].username) {
					user[i].follower[j] = &user[q];
					break;
				}

			}
		}
		user_info.close();
	}

	//read posts
	for (unsigned int i = 0; i < usernum; ++i) {
		for (unsigned int j = 0; j < user[i].num_posts; ++j) {
			ifstream post;
			string directory = userdir + '/' + user[i].username + "/posts/" + to_string(j + 1);
			post.open(directory);

			// check whether it can be opened or not
			try {
				if (!post) {
					ostringstream oStream;
					oStream << "Error: Cannot open file " << directory << '!' << endl;
					throw Exception_t(FILE_MISSING, oStream.str());
				}
			}
			catch (Exception_t& exception) {
				cout << exception.error_info;
				return 0;
			}

			user[i].posts[j].owner = &user[i];
			getline(post, post_s);
			user[i].posts[j].title = post_s;
			num_tags = 0;
			while (getline(post, post_s)) {
				if (post_s[0] == '#') {

					// check whether the number of tags exceeds the maximal number of tags
					try {
						if (num_tags >= MAX_TAGS) {
							ostringstream oStream;
							oStream << "Error: Too many tags for post " << user[i].posts[j].title << '!' << endl;
							oStream << "Maximal number of tags is " << MAX_TAGS << '.' << endl;
							throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
						}
					}
					catch (Exception_t& exception) {
						cout << exception.error_info;
						return 0;
					}

					user[i].posts[j].tags[num_tags] = post_s.substr(1, post_s.length() - 2);
					num_tags++;
					user[i].posts[j].num_tags = num_tags;
				}
				else {
					user[i].posts[j].text = post_s;
					getline(post, post_s);
					stringstream ss;
					ss << post_s;
					ss >> user[i].posts[j].num_likes; // convert string to unsigned int

					// check whether the number of likes exceeds the maximal number of likes
					try {
						if (user[i].posts[j].num_likes > MAX_LIKES) {
							ostringstream oStream;
							oStream << "Error: Too many likes for post " << user[i].posts[j].title << '!' << endl;
							oStream << "Maximal number of likes is " << MAX_LIKES << '.' << endl;
							throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
						}
					}
					catch (Exception_t& exception) {
						cout << exception.error_info;
						return 0;
					}

					for (unsigned int q = 0; q < user[i].posts[j].num_likes; ++q) {
						getline(post, post_s);
						for (unsigned int m = 0; m < usernum; ++m) {
							if (post_s == user[m].username) {
								user[i].posts[j].like_users[q] = &user[m];
								break;
							}
						}
					}
					getline(post, post_s);
					stringstream sss;
					sss << post_s;
					sss >> user[i].posts[j].num_comments; // convert string to unsigned int

					// check whether the number of comments exceeds the maximal number of comments
					try {
						if (user[i].posts[j].num_comments > MAX_COMMENTS) {
							ostringstream oStream;
							oStream << "Error: Too many comments for post " << user[i].posts[j].title << '!' << endl;
							oStream << "Maximal number of comments is " << MAX_COMMENTS << '.' << endl;
							throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
						}
					}
					catch (Exception_t& exception) {
						cout << exception.error_info;
						return 0;
					}

					for (unsigned int q = 0; q < user[i].posts[j].num_comments; ++q) {
						getline(post, post_s);
						for (unsigned int m = 0; m < usernum; ++m) {
							if (post_s == user[m].username) {
								user[i].posts[j].comments[q].user = &user[m];
								getline(post, post_s);
								user[i].posts[j].comments[q].text = post_s;
								break;
							}
						}
					}
					break;
				}
			}
			post.close();
		}
	}

	// read logfile
	while (logfile >> user1) {
		if (user1 == "trending") {
			logfile >> trendn;
			trending(user, trendn, usernum);
		}
		else {
			logfile >> command;
			if (command == "follow") {
				logfile >> user2;
				follow(user, user1, user2, usernum);
			}
			else if (command == "unfollow") {
				logfile >> user2;
				unfollow(user, user1, user2, usernum);
			}
			else if (command == "like") {
				logfile >> user2 >> postid;
				like(user, user1, user2, postid, usernum);
			}
			else if (command == "unlike") {
				logfile >> user2 >> postid;
				unlike(user, user1, user2, postid, usernum);
			}
			else if (command == "comment") {
				logfile >> user2 >> postid;
				getline(logfile, text);  //get "/n"
				getline(logfile, text);
				comment(user, user1, user2, postid, text, usernum);
			}
			else if (command == "uncomment") {
				logfile >> user2 >> postid >> commentid;
				uncomment(user, user1, user2, postid, commentid, usernum);
			}
			else if (command == "post") {
				post(&logfile, user, user1, usernum);
			}
			else if (command == "delete") {
				logfile >> postid;
				unpost(user, user1, postid, usernum);
			}
			else if (command == "refresh") {
				refresh(user, user1, usernum);
			}
			else if (command == "visit") {
				logfile >> user2;
				visit(user, user1, user2, usernum);
			}
		}
	}
	namelist.close();
	logfile.close();
	delete[] user;
	return 0;
}