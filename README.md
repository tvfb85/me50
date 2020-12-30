# SideKick

## Intro

This project is the final assignment in the CS50 course for 2020.

## About

SideKick is an iOS app designed to facilitate communication between those who require shopping assistance during the global pandemic and those who are willing to help.

Whilst the pandemic is ongoing, people in our community who are shielding rely on having their groceries delivered. SideKick offers a way for their shopping requirements to be picked up by someone in the local area who wishes to help out.

Taking a simple ‘to-do’ app to the next level, SideKick allows registered users to create a shopping list which is then searchable by those able to carry out the shop on their behalf. A notification alerts users once the groceries have been delivered on the doorstep, adhering to social distancing measures at all times

## Technologies

- Swift 5.0
- Firebase
- Firestore NoSQL database
- SQLITE3 device storage
- MapKit
- CoreLocation

## Authentication

The app authenticates users with Firebase. Users can register with their firstname, email, password and postcode, and later log in using only their email and password.

During the sign-up/sign-in flow, the password field is validated for the following requirements:

- must contain at least 8 characters
- must use at least one special character
- must include at least one digit

The auth flow creates a user in Firebase and stores data about them (such as their postcode) in the Firestore db.

A user can log out of the app by navigating to the profile section of the site. Upon logout, the user is logged out of Firebase and the app returns to the splash screen.

## App

Once authenticated, the app contains a `UITabBarController` which controls the four main sections of the site:

- [Home](#home)
- [Shopping](#shopping)
- [Friends](#friends)
- [Profile](#profile)

## Home

The homepage uses a `UICollectionView` to show a combination of layouts, with a featured hero image, links to the **Shopping** section of the app, and a carousel of suggested recipes.

## Shopping

Users can create a new shopping list, or update an existing one. Shopping lists which are incomplete are saved under 'Drafts' and the data is stored on the user's device, using SQLITE3. When the user edits a saved draft, the app reads the data back from the device and the user is able to continue editing their list.

When the list is ready, pressing the 'Complete' button will sync the data with Firestore and save the completed list in the `lists` table. A `list` is associated with a Firebase `user` via the `userId` unique identifier.

## Friends

The friends section of the site incorporates MapKit and CoreLocation to plot users on a map based on the postcode they registered with.

On first render, the map zooms to the current user's location.

Custom annotations use a carrot instead of a pin to mark nearby users with active shopping lists. Tapping an annotation shows a customised display with information about that user and their list (i.e. number of grocery items and the time remaining for the list to be fulfilled). The expiry date currently defaults to 7 days from the date the list was created.

The map only plots users who have active, unexpired shopping lists. A user can accept a list to shop on that person's behalf. These lists are identified by a boolean `accepted` flag in the database.

## Profile

Users can edit their personal information, and upon tapping 'Save', the new information is written to the Firestore db.

Users can also log out of the app from this section.

## Improvements

Future developments could include:

- accessing the device's camera to upload a profile photo
- ratings for shoppers
- grocery receipts upload
- contactless payment method

## Presentation

[Youtube](https://youtu.be/82oDUXPZGp0)
