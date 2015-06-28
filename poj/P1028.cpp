/*
 * Problem: Web Navigation
 * http://poj.org/problem?id=1028
 */

#include <string>
#include <stack>
#include <cstdio>

class Browser {
public:
    Browser(std::string initPage) : mCurrentPage(initPage) { }
    void Visit(const std::string& url) {
        mBackStack.push(mCurrentPage);
        mForwardStack = std::stack<std::string>();
        mCurrentPage = url;
        ShowCurrentPage();
    }
    void Back() {
        if (!mBackStack.empty()) {
            mForwardStack.push(mCurrentPage);
            mCurrentPage = mBackStack.top();
            mBackStack.pop();
            ShowCurrentPage();
        } else {
            ShowError();
        }
    }
    void Forward() {
        if (!mForwardStack.empty()) {
            mBackStack.push(mCurrentPage);
            mCurrentPage = mForwardStack.top();
            mForwardStack.pop();
            ShowCurrentPage();
        } else {
            ShowError();
        }
    }
private:
    void ShowCurrentPage() {
        printf("%s\n", mCurrentPage.c_str());
    }
    void ShowError() {
        printf("Ignored\n");
    }
private:
    std::string mCurrentPage;
    std::stack<std::string> mBackStack;
    std::stack<std::string> mForwardStack;
};

int main() {
    char buff[128];
    Browser browser("http://www.acm.org/");
    while (true) {
        scanf("%s", buff);
        std::string Command(buff);
        if (Command == "VISIT") {
            scanf("%s", buff);
            std::string url(buff);
            browser.Visit(url);
        } else if (Command == "BACK") {
            browser.Back();
        }
        else if (Command == "FORWARD") {
            browser.Forward();
        } else if (Command == "QUIT") {
            break;
        }
    }
    return 0;
}
