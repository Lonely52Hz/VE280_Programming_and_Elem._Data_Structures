/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */
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

// TODO: Define your functions in this header file.

// EFFECT: implementation of visit function and print corresponding answer
void visit(User_t user[], string user1, string user2, unsigned int usernum) {
    cout << ">> visit" << endl;
    unsigned int user1id = 0;
    unsigned int user2id = 0;
    unsigned int isFollowing = 0;
    unsigned int isMutualFollowing = 0;
    unsigned int isMyself = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            user1id = i;
            break;
        }
    }
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user2 == user[i].username) {
            user2id = i;
            break;
        }
    }
    if (user1id == user2id) {
        isMyself = 1;
    }
    else {
        for (unsigned int i = 0; i < user[user1id].num_following; ++i) {
            if (user[user1id].following[i]->username == user2) {
                isFollowing = 1;
                break;
            }
        }
        for (unsigned int i = 0; i < user[user1id].num_followers; ++i) {
            if (user[user1id].follower[i]->username == user2) {
                isMutualFollowing = 1;
                break;
            }
        }
    }
    if (isFollowing == 1 && isMutualFollowing == 1) {
        printUser(user[user2id], "friend");
    }
    else if (isFollowing == 1 && isMutualFollowing == 0) {
        printUser(user[user2id], "following");
    }
    else if (isFollowing == 0) {
        printUser(user[user2id], "stranger");
    }
    else if (isMyself == 1) {
        printUser(user[user2id], "");
    }
}

// EFFECT: implementation of trending function and print corresponding answer
void trending(User_t user[], unsigned int trendn, unsigned int usernum) {
    cout << ">> trending" << endl;
    Tag_t* tag = new Tag_t[5000];
    unsigned int tagnum = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        for (unsigned int j = 0; j < user[i].num_posts; ++j) {
            for (unsigned int q = 0; q < user[i].posts[j].num_tags; ++q) {
                unsigned int isExist = 0;
                for (unsigned int m = 0; m < tagnum; ++m) {
                    if (user[i].posts[j].tags[q] == tag[m].tag_content) {
                        isExist = 1;
                        tag[m].tag_score += 5 + 3 * user[i].posts[j].num_comments + user[i].posts[j].num_likes;
                        break;
                    }
                }
                if (isExist == 0) {
                    tag[tagnum].tag_content = user[i].posts[j].tags[q];
                    tag[tagnum].tag_score = 5 + 3 * user[i].posts[j].num_comments + user[i].posts[j].num_likes;
                    tagnum++;
                }
            }
        }
    }

    // first sort by ASCII
    for (unsigned int i = 0; i < tagnum - 1; ++i) {
        for (unsigned int j = 0; j < tagnum - 1 - i; ++j) {
            if (tag[j].tag_content.compare(tag[j + 1].tag_content) > 0) {
                Tag_t temp = tag[j + 1];
                tag[j + 1] = tag[j];
                tag[j] = temp;
            }
        }
    }

    // then sort by score
    for (unsigned int i = 0; i < tagnum - 1; ++i) {
        for (unsigned int j = 0; j < tagnum - 1 - i; ++j) {
            if (tag[j].tag_score < tag[j + 1].tag_score) {
                Tag_t temp = tag[j + 1];
                tag[j + 1] = tag[j];
                tag[j] = temp;
            }
        }
    }
    for (unsigned int i = 1; i < min(tagnum, trendn) + 1; ++i) {
        printTag(tag[i - 1], i);
    }
    delete[] tag;
}

// EFFECT: implementation of refresh function and print corresponding answer
void refresh(User_t user[], string user1, unsigned int usernum) {
    cout << ">> refresh" << endl;
    unsigned int userid = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            userid = i;
            break;
        }
    }
    for (unsigned int i = 0; i < user[userid].num_posts; ++i) {
        printPost(user[userid].posts[i]);
    }
    for (unsigned int i = 0; i < user[userid].num_following; ++i) {
        for (unsigned int j = 0; j < user[userid].following[i]->num_posts; ++j) {
            printPost(user[userid].following[i]->posts[j]);
        }
    }
}

// EFFECT: implementation of follow function
void follow(User_t user[], string user1, string user2, unsigned int usernum) {
    cout << ">> follow" << endl;
    unsigned int user1id = 0;
    unsigned int user2id = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            user1id = i;
            break;
        }
    }
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user2 == user[i].username) {
            user2id = i;
            break;
        }
    }
    user[user1id].following[user[user1id].num_following] = &user[user2id];
    user[user2id].follower[user[user2id].num_followers] = &user[user1id];
    user[user1id].num_following++;
    user[user2id].num_followers++;
}

// EFFECT: implementation of unfollow function
void unfollow(User_t user[], string user1, string user2, unsigned int usernum) {
    cout << ">> unfollow" << endl;
    unsigned int user1id = 0;
    unsigned int user2id = 0;
    unsigned int followid = 0;
    unsigned int followerid = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            user1id = i;
            break;
        }
    }
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user2 == user[i].username) {
            user2id = i;
            break;
        }
    }
    for (unsigned int i = 0; i < user[user1id].num_following; ++i) {
        if (user[user1id].following[i]->username == user2) {
            followid = i;
            break;
        }
    }
    for (unsigned int i = followid; i < user[user1id].num_following - 1; ++i) {
        user[user1id].following[i] = user[user1id].following[i + 1];
    }
    for (unsigned int i = 0; i < user[user2id].num_followers; ++i) {
        if (user[user2id].follower[i]->username == user1) {
            followerid = i;
            break;
        }
    }
    for (unsigned int i = followerid; i < user[user2id].num_followers - 1; ++i) {
        user[user2id].follower[i] = user[user2id].follower[i + 1];
    }
    user[user1id].num_following--;
    user[user2id].num_followers--;
}

// EFFECT: implementation of like function
void like(User_t user[], string user1, string user2, unsigned int postid, unsigned int usernum) {
    cout << ">> like" << endl;
    unsigned int user1id = 0;
    unsigned int user2id = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            user1id = i;
            break;
        }
    }
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user2 == user[i].username) {
            user2id = i;
            break;
        }
    }

    try {
        //Check whether <user 2> has posted post <post_id>
        if (user[user2id].num_posts < postid) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot like post #" << postid << " of " << user2 << '!' << endl;
            oStream << user2 << " does not have post #" << postid << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        unsigned int isLike = 0;
        for (unsigned int i = 0; i < user[user2id].posts[postid - 1].num_likes; ++i) {
            if (user1 == user[user2id].posts[postid - 1].like_users[i]->username) {
                isLike = 1;
                break;
            }
        }
        //Check whether <user 1> has already liked the post <post_id> of <user 2>
        if (isLike == 1) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot like post #" << postid << " of " << user2 << '!' << endl;
            oStream << user1 << " has already liked post #" << postid << " of " << user2 << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else {
            user[user2id].posts[postid - 1].like_users[user[user2id].posts[postid - 1].num_likes] = &user[user1id];
            user[user2id].posts[postid - 1].num_likes++;
        }
    }
    catch (Exception_t& exception) {
        cout << exception.error_info;
    }
}

// EFFECT: implementation of unlike function
void unlike(User_t user[], string user1, string user2, unsigned int postid, unsigned int usernum) {
    cout << ">> unlike" << endl;
    unsigned int user2id = 0;
    unsigned int likeid = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user2 == user[i].username) {
            user2id = i;
            break;
        }
    }

    try {
        //Check whether <user 2> has posted post <post_id>
        if (user[user2id].num_posts < postid) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot unlike post #" << postid << " of " << user2 << '!' << endl;
            oStream << user2 << " does not have post #" << postid << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        unsigned int isUnlike = 1;
        for (unsigned int i = 0; i < user[user2id].posts[postid - 1].num_likes; ++i) {
            if (user1 == user[user2id].posts[postid - 1].like_users[i]->username) {
                isUnlike = 0;
                likeid = i;
                break;
            }
        }
        //Check whether <user 1> has already liked the post <post_id> of <user 2>
        if (isUnlike == 1) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot unlike post #" << postid << " of " << user2 << '!' << endl;
            oStream << user1 << " has not liked post #" << postid << " of " << user2 << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else {
            for (unsigned int i = likeid; i < user[user2id].posts[postid - 1].num_likes - 1; ++i) {
                user[user2id].posts[postid - 1].like_users[i] = user[user2id].posts[postid - 1].like_users[i + 1];
            }
            user[user2id].posts[postid - 1].num_likes--;
        }
    }
    catch (Exception_t& exception) {
        cout << exception.error_info;
    }
}

// EFFECT: implementation of comment function
void comment(User_t user[], string user1, string user2, unsigned int postid, string text, unsigned int usernum) {
    cout << ">> comment" << endl;
    unsigned int user1id = 0;
    unsigned int user2id = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            user1id = i;
            break;
        }
    }
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user2 == user[i].username) {
            user2id = i;
            break;
        }
    }

    try {
        //Check whether <user 2> has posted post <post_id>
        if (user[user2id].num_posts < postid) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot comment post #" << postid << " of " << user2 << '!' << endl;
            oStream << user2 << " does not have post #" << postid << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else {
            user[user2id].posts[postid - 1].comments[user[user2id].posts[postid - 1].num_comments].text = text;
            user[user2id].posts[postid - 1].comments[user[user2id].posts[postid - 1].num_comments].user = &user[user1id];
            user[user2id].posts[postid - 1].num_comments++;
        }
    }
    catch (Exception_t& exception) {
        cout << exception.error_info;
    }
}

// EFFECT: implementation of uncomment function
void uncomment(User_t user[], string user1, string user2, unsigned int postid, unsigned int commentid, unsigned int usernum) {
    cout << ">> uncomment" << endl;
    unsigned int user2id = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user2 == user[i].username) {
            user2id = i;
            break;
        }
    }

    try {
        //Check whether <user 2> has posted post <post_id>
        if (user[user2id].num_posts < postid) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot uncomment comment #" << commentid << " of post #" << postid << " posted by " << user2 << '!' << endl;
            oStream << user2 << " does not have post #" << postid << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        //Check whether post <post_id> of <user 2> has comment <comment_id>
        if (user[user2id].posts[postid - 1].num_comments < commentid) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot uncomment comment #" << commentid << " of post #" << postid << " posted by " << user2 << '!' << endl;
            oStream << "Post #" << postid << " does not have comment #" << commentid << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        unsigned int isOwner = 0;
        if (user[user2id].posts[postid - 1].comments[commentid - 1].user->username == user1) {
            isOwner = 1;
        }
        //Check whether <user 1> is the owner of comment <comment_id>
        if (isOwner == 0) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot uncomment comment #" << commentid << " of post #" << postid << " posted by " << user2 << '!' << endl;
            oStream << user1 << " is not the owner of comment #" << commentid << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else {
            for (unsigned int i = commentid - 1; i < user[user2id].posts[postid - 1].num_comments - 1; ++i) {
                user[user2id].posts[postid - 1].comments[i] = user[user2id].posts[postid - 1].comments[i + 1];
            }
            user[user2id].posts[postid - 1].num_comments--;
        }
    }
    catch (Exception_t& exception) {
        cout << exception.error_info;
    }
}

// EFFECT: implementation of post function
void post(ifstream* logfile, User_t user[], string user1, unsigned int usernum) {
    cout << ">> post" << endl;
    string title;
    string text;
    getline(*logfile, title);  //get "/n"
    unsigned int userid = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            userid = i;
            break;
        }
    }
    getline(*logfile, title);
    user[userid].posts[user[userid].num_posts].title = title;
    unsigned int numtags = 0;
    while (getline(*logfile, text)) {
        if (text[0] == '#') {
            user[userid].posts[user[userid].num_posts].tags[numtags] = text.substr(1, text.length() - 2);
            numtags++;
            user[userid].posts[user[userid].num_posts].num_tags = numtags;
        }
        else {
            user[userid].posts[user[userid].num_posts].text = text;
            break;
        }
    }
    user[userid].posts[user[userid].num_posts].num_comments = 0;
    user[userid].posts[user[userid].num_posts].num_likes = 0;
    user[userid].posts[user[userid].num_posts].owner = &user[userid];
    user[userid].num_posts++;
}

// EFFECT: implementation of delete function
void unpost(User_t user[], string user1, unsigned int postid, unsigned int usernum) {
    cout << ">> delete" << endl;
    unsigned int user1id = 0;
    for (unsigned int i = 0; i < usernum; ++i) {
        if (user1 == user[i].username) {
            user1id = i;
            break;
        }
    }

    try {
        //Check whether <user 1> has posted post <post_id>
        if (user[user1id].num_posts < postid) {
            ostringstream oStream;
            oStream << "Error: " << user1 << " cannot delete post #" << postid << '!' << endl;
            oStream << user1 << " does not have post #" << postid << '.' << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else {
            for (unsigned int i = postid - 1; i < user[user1id].num_posts - 1; ++i) {
                user[user1id].posts[i] = user[user1id].posts[i + 1];
            }
            user[user1id].num_posts--;
        }
    }
    catch (Exception_t& exception) {
        cout << exception.error_info;
    }
}

/* Helper Functions */

// Printing

void printUser(User_t& user, const string& relationship) {
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
        << "\nFollowing: " << user.num_following << endl;
}


void printPost(Post_t& post) {
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for (unsigned int i = 0; i < post.num_tags; ++i) {
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0) {
        cout << "Comments:" << endl;
        for (unsigned int i = 0; i < post.num_comments; ++i) {
            cout << post.comments[i].user->username << ": "
                << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}


void printTag(const Tag_t& tag, unsigned int rank) {
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
