# Overview
Ever wish you didn't have to carry those bulky keys around? Well now you can with the super advanced Shrek Swiping System! Designed to take in an RFID Card and automatically open a door for you, we have added a scary Shrek mechanism to make sure nobody will ever try to enter your home or dorm unauthorized ever again.

## Inspiration
Both of us have been the victims of becoming locked out of our dorm rooms at night after a long study session in one of Berkeley's many libraries - and we wished that we could swipe into our room the same way that we could swipe into the dorm buildings.

## How we built it
We used two Arduino Nano's, an LCD, two RF transceivers, and more wires than Jeff Bezos probably has in money in order to create a circuit that was segmented into two parts: The first circuit would scan the RFID Card and verify that the person was the correct individual signing in. They would send this value to the second circuit, which either rickrolls you if you are the correct individual, or brings out the big scary Shrek™ and scares the individual from every attempting to break in ever again :)

## Challenges we ran into
Like Milk Tea and Boba, learning new things always come with obstacles. One of those obstacles was when we wanted to use multiple SPI modules on a singular bus. Because we were using an Arduino Nano, it made it difficult to fit all the wires and pins together, leading to obstacles with the select system that SPI employs - specifically on how our RFID module seemed to have some kind of override for it. We racked our brains for __hours__ trying to figure out a solution - and right after finding one, a catastrophe came our way. Somehow, an ominously open can of Mountain Dew flooded the table, breaking apart the SPI system and almost bricking our entire project. After a while of not being able to get the Arduino working again, we almost decided to head home and get some sleep.

But we decided to give it just one more try. Rewiring the board once again carefully worked - allowing us to stay up and finish our project.

And that is why we have sworn to **never** drink Mountain Dew again in our lives.

## Accomplishments that we're proud of
This was both of our first time's working with RFID, and we are proud of the fact that we learned **a lot** throughout this process working with that and other technologies. Every time we came across an obstacle and found a solution, we felt like we were expanding our knowledge in the amazing world of hardware.

## What we learned
We came into this hackathon knowing two things:
- We wanted to build a hardware project
- We know almost nothing about hardware.

And so when hacking started two days ago, the long and arduous effort began to learn how in the world we were going to build this thing. At times we didn't really know if we would be able to solve an obstacle or worried that we didn't have the prerequisite knowledge to finish this project. But throughout this project, we feel as if we gained a good understanding of the Arduino, RFID technologies, and hardware in general.

## What's next for Shrek Swiping System (SSS)
the Shrek Swiping System (SSS) has a long way ahead of itself. We really want to implement this solution in our own dorms, add a custom 3D print to clean up the setup, add the ability to customize the music for each individual who comes to witness the marvel that is the Shrek Swiping System (SSS)™.
