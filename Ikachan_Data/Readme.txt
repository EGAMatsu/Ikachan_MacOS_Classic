
Bite-sized action-adventure game
        >> Ikachan <<

      By Studio Pixel

This game is designed to run on Windows.

<How To Run>
Double-click Ikachan.exe

<How to Play>
Left, Right: Tilt / Change selection choice
Z: Thrust / Make selection
S: Open inventory

<Warning>
Save data is stored in the file "Ika.rec"
Starting the game over from the beginning will overwrite this file.

<Development Time>
One month plus a little bit.

---------------------
This is free software.
The developer is not responsible for any issues that may arise.
(This software was produced in good faith. We appreciate your understanding.)

URL(new) - https://studiopixel.jp/
URL(old) - http://hp.vector.co.jp/authors/VA022293/


--------------------------------------------
--------------------------------------

TRANSLATOR'S CREDITS AND NOTES

Version 1.5.2.0 modification and English translation: IdioticBaka1824.
Thanks, drippingyellow, for the pointers on what to modify. Also shoutout to AquaDoesStuff for suggesting the idea of retranslation. And thanks chocolattedog, andwhyisit for playtesting.
Decompilation: CuckyDev
Version 1.4.2.0 English translation: PhoenixJ

The original translation by PhoenixJ took some creative liberties and produced dialogue that was very rich and flavourful, providing an enjoyable playing experience, but was also rather inaccurate to the original in many places.
This translation aims to achieve a more faithful and literal rendition of the original script. My general philosophy is essentially not to add anything that's not already in there.
Various online dictionaries (contextual and otherwise), as well as language forums, were consulted to improve upon a base machine translation.

Note: I have not played or seen Nicalis's localisation (and I do not intend to do so).

----------------------
Translation notes:
----------------------

~README~
The development time, as can be seen in the credits, was way more than a month. Why does the readme say it's one month? Maybe as a joke? Like, "it was supposed to take a month, and it kept getting stretched out by 'just a little more'... until it ended up taking a few years" kinda thing?

~CHARACTERS~

Most of the characters do not have names. The names listed on the Tribute Site (cavestory.org) page are transcriptions of comments in the script used to describe their events - this is often just some keyword associated with the character:
Oku = depths (he's hiding underground)
Onbin = easy-going (he describes himself as easy-going)
Setsumei = explanation (he gives you the explanatory note on pearls)
Jishin = earthquake (he talks about the earthquakes causing cracks to appear)
Erasou = looks important (she refers to Carry as such)
Oto = sound (he tells you about the invulnerability sound effect)

These characters have real names and are canonically referred to as such in-game:
Fooze = 'foods' transcribed to Japanese phonology (the Tribute Site lists him only as Pinky's father)
Pinky = is pink.
Ironhead = has an iron head.
Zuu is referred to internally as 'zoo', perhaps referring to the attack stars being kept in cages.
Pearl Carrier is just that, spelled out in katakana. (He is referred to internally as Carry.) Now, 'Pearl Carrier' seems a little awkward to use as a regular name -- maybe because it's too common noun-y? I guess the lore is that he's explicitly calling himself someone who carries a pearl in order to give himself more legitimacy. Or maybe it's not that deep. For a while I considered using 'Pearl Carrier' as a title instead, with Carry being a nickname, but then I figured hey, let's just stick to the script.

---------------------

~EVENTS/DIALOGUE~

(It's best to have a copy of Event.ptx open on the side for reference while you're reading this.)

#e0000/#e0001/#e0008
I think most people would want to continue their saved game, so having 'start new game' as the default option was a little risky and annoying (especially considering this automatically overwrites your save). So I switched the yes and no options around from the original, so that just pressing Z in the beginning lets you continue instead of restart.
The game originally asks in #e0001 if you want to start a new game, and if you choose no it continues in the same event to run a load game command <dl, while if you choose yes it jumps to #e0000 which is a 'dummy' event with nothing in it. Initially, to effect the switch, I just put the <dl in #e0000, but then I noticed that everytime you kill an enemy you jump back to the save point - it seems like the dummy #e0000 is run on all enemy deaths??? So I made a new event #e0008 to jump to for game loading purposes. That was funny.

#e0004
I was actually considering changing this to a standard game phrase like 'health refilled', but it literally says 'good morning', which was cute, so I kept it.

#e0006/#e0007
Same sort of yes/no flipping as with #e0001. I think the default option should be to retry, not to exit.
Also, the original text was something like 'you fell apart and got scattered'. In English, getting bown to smithereens is the only phrase I know for dying that references getting disintegrated like that, but it suggests a more violent, explosive image. I wish I could come up with something better. But it didn't seem right to replace the evocative image of falling apart with a plain and staid 'you have died' message.

#e0058/#e0114
Zuu uses 「ワシ」 ('washi') to refer to himself, and uses 「じゃ」 ('ja') instead of the standard 「だ」 ('da') as the copula. This is stereotypical old man talk, as well as somewhat dialectal. Interestingly, he's a little inconsistent with it, with the accent showing up more strongly in the endgame. Maybe Pixel kinda started leaning into it more as he went along during development? (Ironically, it's in the endgame where I wasn't able to express the accent as much.)
Also, his use of 「連中」 ('renchuu') to refer to the others also suggests he does not feel like he is part of them - he's a bit of a paranoid old hermit holed up and away from Ironhead's realm.

#e0088
Yes, I took 'right-fin man' straight from the description on the Tribute Site page.

#e0097
I still think it's weird for a kid to be giving us all this lore exposition.

#e0099/#e0100
I'm trying to keep the nuance between 「娘」 ('musume') and 「子」 ('ko') by translating them as 'girl' and 'daughter' respectively.
Literally speaking, the other way around may seem like the more accurate translation choice, but idiomatically I think this way it suits the father and mother's speech patterns better, respectively.

#e0108
Ben says 'Hey, Johnny!' in English. He also talks in an informal, familiar but 'rough' manner.
After he mentions you look like a squid, there's a pause (marked with an ellipsis) before he moves on with the conversation. Given the writing style in this game, I feel like that wouldn't have been written out otherwise, and here it was deliberately done to subtly call attention to the fact that we thought the player was really a squid all along, like Ben is taking a dig at the absurdity of the game. I chose to incorporate this as '...Aaanyways' (which also doesn't sound too out of place considering his speech does drag out the vowels a bit.)
The part I translated as 'Ben joined you' literally uses the same phrasing as with all other items, but it seems a little weird in English to say 'You got Ben' for this, so, yeah.

#e0113
「そうか」 ('sou ka') is generally translated as 'I see', but somehow that didn't seem to fit. Fooze seemed to be making a generic sound of approval, but he was excited enough to use an exclamation mark, so I went with the contextually appropriate-seeming 'that's wonderful'.

#e0116
You will not believe how hard it was to restrain myself from writing this as "Carry was carried onto the ship".

#e0125
PhoenixJ translated this sign as 'curiosity killed the cat'. Considering how you can actually get out of this danger room if you have the capacitor, I was considering having the sign change to 'satisfaction won it back' once you get the capacitor. That would be funny. But ultimately that goes against the goal of this translation, so unfortunately this opportunity was passed up and I played it straight.

#e0126
「いかした」 ('ikashita') means stylish, but 'ika' was spelled out in katakana and means 'squid'. So this is a pun on how the the hat makes Ikachan look like a squid. It was hard to keep the squid meaning, but I was able to maintain a pun of some sort by using 'sharp' to refer to the hat's ability as a weapon, as well as it being fashionable.

#e1001
Literally, the conversation has three lines that go like 'I haven't eaten anything'. 'You can tell by the size of my body'. 'I eat more than most people'.
Now, given the lack of ordinating conjunctions, it's hard to tell which statements were intended as causally connected: is it like 'You can tell that I eat more than most people by how big my body is', or is it like 'You can tell I haven't eaten anything by how small my body is'?
...Is what I was confused about for a while, but then I noticed that the dialogue box is cleared after the first of these sentences, so the latter interpretation can't be right. I guess it goes to show how it pays to actually play-test first instead of just reading the script in a text editor.

#e1002
This line originally didn't have a click-to-continue, causing the message box to disappear right away without you pressing anything. I assumed this was a mistake, and fixed it.

#e1003
「迎えが来た」 ('mukae ga kita') is generally used in the sense of 'my ride is here', but clearly Ironhead wasn't expecting to be picked up, so what does he mean? Apparently 迎え can also mean 'to approach a time or a point in your life'. Combined with the talk of hunger earlier, I figured he was basically saying he thought we were the grim reaper. Typically you'd say 'I thought my time had come', but the link to thinking we were death tapping on his shoulder needed to be emphasised, so I made it 'I thought it was my time that had come', a construction otherwise used for more tangible things.

Credits (Staff.ptx):
I changed the names to surname-last order.
Unfortunately, here the text was rendered one line at a time, so there was no way to include star characters and the like by switching to a different font and everything. (I mean, not like it's impossible, but it wasn't worth it.)
Now I really want to know what equipment Pixel went to a hospital for just to make a game.
I have no idea what a 'File Tricker' is supposed to be. Google only points back to this very credits file. It's probably an inside joke. The world will never know.
One line said 「↑没です」 ('botsu desu', i.e. 'rejected'). I couldn't replicate the arrow for the aforementioned reasons, so to keep the informal tone it conveyed, I made it 'this was rejected btw'.
Also interestingly Pixel was very inconsistent about putting a colon after role titles or not, I just used one for them all.
Also also, there's a typo in one name: 'Mashaharu'

----------------

~ITEMS~

#e2001-#e2004
The first few items only start a new line after showing the item name, while the later items clear the message box. I assume the latter behaviour is what Pixel decided on partway through development, and is thus the intended behaviour - but he forgot to go back and change it for the earlier items. With this assumption, I have fixed these items so that they clear the message box as well.

#e0122/#e2001
Apparently 「とんがり帽子」 ('tongari boushi') as a phrase commonly refers to the pointed hats associated with witches. As such I chose to translate it with the set phrase 'pointed hat', rather than use 'cap'.

#e0075/#e2002
The original is 「スカシカシパン」 ('sukashikashipan'), the name for a Sand Dollar (the animal, of order Clypeasteroida). But 「菓子パン」 ('kashipan') also refers to a variety of sweet-filled breads in Japan. 'Sandwich Dollar' is the best I could come up with to combine a sand dollar with something edible.
Well, maybe the original wasn't really a pun, considering the animal was named for its similarity to the bread.

#e0076/#e2006
「エビ料理」 ('ebi ryouri') usually refers to 'shrimp-based cuisine' or 'shrimp dishes in general'. So, 'shrimp platter' was the most generic thing I could come up with that could still refer to a particular meal. Similarly for the crab and globefish. I guess PhoenixJ's translation chose terms like 'cocktail' and 'soup' to change it up a bit because using the same word for all three is a bit weird, but translating more literally is my goal here, so, yeah.

#e0095/#e2008
It's interesting that in Japanese it's called a 「コンデンサ」 ('condenser'), which is also what it was called in English until the early 1900s (around which the name shifted to 'capacitor' to avoid ambiguity with the steam condensor, apparently). The fact that the Japanese Wikipedia page mentions the German name 'Kondensator' may have something to do with this?

#e2011
Typically, putting an item name in quotation marks serves to highlight that it's an Item with a capital I that can be obtained as the player character, which is why it's not so weird for characters to be saying item names with quotes around them in their dialogue. Here, the quotation marks are in the item description itself, which, along with the context, suggests that the purpose is more like scare quotes.

#e3000
This is the health-refilling event that runs when you drink the strange liquid. Strangely, the comment next to the event number says 'kashipan', referring to the sandwich dollar. This perhaps suggests that the sandwich dollar was originally mean to be edible, before being repurposed for the pearl plot point and the strange liquid being introduced as the designated health refill item in its place.

--------------------

~PROGRAMMING~

The script-processing function in the decompiled source code did a few checks: If the character code was over 0x80, it assumed the following two bytes were a Shift-JIS character and wrote them that way. Otherwise, if the character was between 'A' and 'z' or between '0' and '9', it was treated as an ASCII character to write. Then there were a few character handled on a case-by-case basis: ~, ., and , were ignored; + was used as a newline; and { was used as a click-to-continue indicator.
The major modification made here was to extend the range of the ASCII checking to between ' ' and 'z', so that common characters like space, !, and ? would fall within this scope and be treated normally. Then the special characters + and { had to be excluded from that check manually.
For aesthetic purposes I changed the size/spacing of each character from 8 to 6, because fullwidth CJK characters take up more space than Latin characters and the translated text was looking a little too spread out.
I guess I'll also mention this for completeness: I changed length of the drop-down box in the start-up screen, so that the word 'windowed' wouldn't get cut off by one letter. And then I shifted it and the buttons under it and the line on the left all leftward a bit to keep the padding on the right edge. And made the buttons a tad longer to reduce the now-increased space in between them. Why am I even documenting all of this.

-----------------------
2025-05-15 ~ 2025-05-24