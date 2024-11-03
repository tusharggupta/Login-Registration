#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <curl/curl.h>  

using namespace std;

string generateOTP() {
    srand(time(0)); // Random number generation
    int otp = rand() % 900000 + 100000; // Generates a 6-digit number
    return to_string(otp);
}

bool sendEmail(const std::string& recipient, const std::string& otp) {
    CURL* curl;
    CURLcode res;

    std::string apiKey = "";  
    std::string apiSecret = ""; 
    std::string fromEmail = ""; 
    std::string subject = "Your OTP Code";
    std::string content = "Your OTP is: " + otp;

    std::string jsonPayload = R"({
        "Messages":[
            {
                "From": {
                    "Email": ")" + fromEmail + R"(",
                    "Name": "Your Name"
                },
                "To": [
                    {
                        "Email": ")" + recipient + R"(",
                        "Name": "User"
                    }
                ],
                "Subject": ")" + subject + R"(",
                "TextPart": ")" + content + R"("
            }
        ]
    })";

    curl = curl_easy_init();
    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.mailjet.com/v3.1/send");
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_USERNAME, apiKey.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, apiSecret.c_str());

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            return false;
        }

        curl_easy_cleanup(curl);
        return true;
    }
    return false;
}

void registerUser() {
    string username, password, email;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;
    cout << "Enter your email: ";
    cin >> email;

    string otp = generateOTP();
    if (!sendEmail(email, otp)) {
        cout << "Failed to send OTP. Please try again." << endl;
        return;
    }

    cout << "An OTP has been sent to your email. Please enter it below." << endl;
    string enteredOtp;
    cout << "Enter OTP: ";
    cin >> enteredOtp;

    if (enteredOtp == otp) {
        ofstream file("users.txt", ios::app);
        file << username << " " << password << " " << email << endl;
        file.close();
        cout << "Registration successful!" << endl;
    } else {
        cout << "Incorrect OTP. Registration failed." << endl;
    }
}

bool loginUser() {
    string username, password, storedUser, storedPass, storedEmail;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    bool loginSuccess = false;

    while (file >> storedUser >> storedPass >> storedEmail) {
        if (storedUser == username && storedPass == password) {
            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        string otp = generateOTP();
        if (!sendEmail(storedEmail, otp)) {
            cout << "Failed to send OTP. Please try again." << endl;
            return false;
        }

        cout << "An OTP has been sent to your email. Please enter it below." << endl;
        string enteredOtp;
        cout << "Enter OTP: ";
        cin >> enteredOtp;

        if (enteredOtp == otp) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Incorrect OTP." << endl;
            return false;
        }
    } else {
        cout << "Incorrect username or password." << endl;
        return false;
    }
}

int main() {
    int choice;

    cout << "Welcome to the Login and Registration System" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        registerUser();
    } else if (choice == 2) {
        loginUser();
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
