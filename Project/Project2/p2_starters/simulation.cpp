/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "simulation.h"

// TODO: Define your functions in this header file.
void visit(...);

void trending(User_t& user, unsigned int trendn);

void refresh(...);

void follow(User_t& user, string user1, string user2);

void unfollow(User_t& user, string user1, string user2);

void like(User_t& user, string user1, string user2, unsigned int postid);

void unlike(User_t& user, string user1, string user2, unsigned int postid);

void comment(User_t& user, string user1, string user2, unsigned int postid, string text);

void uncomment(User_t& user, string user1, string user2, unsigned int postid, unsigned int commentid);

void post() {
    cout << ">> post" << endl;
}

void unpost(...);

/* Helper Functions */

// Printing

void printUser(User_t& user, const string& relationship){
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}


void printPost(Post_t& post){
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(unsigned int i = 0; i<post.num_tags; ++i){
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0){
        cout << "Comments:" << endl;
        for(unsigned int i = 0; i<post.num_comments; ++i){
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}


void printTag(const Tag_t& tag, unsigned int rank){
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
