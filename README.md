# Payment System

Payment System is a C project that simulates a payment application.\
It allows users to enter their card and transaction details and checks if the payment is valid and approved.

## Installation

To install Payment System, you need to have a C compiler and a terminal.\
You can use any C compiler of your choice, such as GCC or Clang.\
You also need to download the source code files from this repository.

To compile the project, navigate to the directory where you downloaded the source code files and run the following command:

```bash
gcc main.c -o payment

This will create an executable file called payment in the same directory.

Usage
To run the project, execute the following command in the terminal:

./payment
```
This will start the payment application and prompt you to enter your card and transaction details.
## You need to enter the following information:
Card holder name: The name should be from 20 to 24 characters.\
Card PAN: The PAN should range from 16 to 19 digits.\
Card expiry date: The date should be in the format MM/YY.\
Transaction date: The date should be in the format DD/MM/YYYY.\
Max amount: The maximum amount that can be paid with the card.\
Transaction amount: The amount that you want to pay.\
The application will then validate your input and check if the payment is approved or declined. 
## It will display one of the following messages:

Approved: The payment is successful and the transaction is completed.\
DECLINED_INSUFFICIENT_FUND: The payment is declined because the card balance is insufficient.\
DECLINED_STOLEN_CARD: The payment is declined because the card is reported as stolen.\
FRAUD_CARD: The payment is declined because the card is suspected to be fraudulent.\
You can exit the application by pressing Ctrl+C.

## Contributing
Payment System is an open source project and welcomes contributions from anyone who is interested.\

If you want to contribute, please follow these steps:\
Fork this repository and clone it to your local machine.\
Create a new branch for your feature or bug fix.\
Make your changes and commit them with a clear and descriptive message.\
Push your branch to your forked repository and create a pull request to the main repository.\
Wait for your pull request to be reviewed and merged.

Please make sure to follow the coding style and conventions of the project and update the documentation and tests as appropriate.

### I hope this helps you with your project. If you have any questions or feedback, please let me know. 😊
