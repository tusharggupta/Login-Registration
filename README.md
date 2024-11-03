# Login-Registration
Developed a C++ application for secure user login and registration with OTP (One-Time Password) verification. Users register with a username, password, and email, followed by OTP verification during login and registration. The application enhances security by utilizing the Mailjet API to send OTPs via email.
Here's a comprehensive description of the C++ project you've built:

### Project Overview
Developed a C++ application for user login and registration with OTP (One-Time Password) verification. The application allows users to register with a username, password, and email, and then login securely using a password. For an added layer of security, both the registration and login processes include OTP validation via email, utilizing the Mailjet API.

### Key Components

1. **OTP Generation and Validation:**
   - The program generates a six-digit OTP using C++'s random number functions. 
   - This OTP is emailed to the user for verification, which provides an extra security step in both registration and login.

2. **Email API Integration:**
   - The `curl` library is integrated to make API calls to Mailjet for sending OTP emails. The API keys and email details are defined in the code for authentication with the Mailjet service.

3. **User Data Storage:**
   - User information, including username, password, and email, is stored in a `users.txt` file.
   - During registration, this file is appended with the user's data, and during login, it is used to validate credentials by matching the username and password.

4. **Error Handling and User Feedback:**
   - The code handles OTP email-sending failures by checking the result of the Mailjet API call.
   - If the OTP entered does not match, the program notifies the user of a failed registration or login attempt.

5. **Masked Password Input (Optional Feature):**
   - To enhance security during password input, a masked password input function (like using `termios` for UNIX) could be implemented. However, this feature is not essential for functionality but would improve user experience.

6. **Security Considerations:**
   - While OTP provides some security, consider encrypting or hashing passwords before storing them in `users.txt` to add further protection.

### Steps to Run the Application

1. **Compile the Code:**  
   Use the following command to compile the code, linking the `curl` library:
   ```bash
   g++ -o main loginRegistration.cpp -lcurl
   ```

2. **Execute the Application:**  
   Run the compiled program using:
   ```bash
   ./main
   ```

3. **Using the Application:**
   - Select **1** to register, and after entering your information, check your email for the OTP.
   - Select **2** to log in, entering your credentials and verifying with the OTP sent to your registered email.

This C++ application is a comprehensive example of combining file-based storage with external API integration and security practices, providing a functional command-line-based login and registration system with OTP verification.
