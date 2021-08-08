// ------------ VERSION 1 -------------------- //
/*
// This is where we do our authentication bit
import asyncHandler from 'express-async-handler';
import User from '../models/userModel.js';

// First we will authenticate the user and then get the token.
// Obviously this is going to be a POST request.
// Our route will be /api/users/login.
// as this is the backend we can use our asyncHandler instead of try catch for our
// async request.
// ** Remember that whenever you do a POST request. The JSON response you get back will always be 
// found in the request object's body key.
const authUser = asyncHandler( async (req, res) => {

    // Get the data from the request body
    const {email, password} = req.body;
    // get the  details of the user with that email
    const user = await User.findOne({email});

    // if the user exists
    if (user ) {
        // For our password matching, we will make a function in our 
        // userModel.js. For now we can send some json data back.
        res.json({
            _id: user._id,
            name: user.name,
            email: user.email,
            isAdmin: user.isAdmin,
            // for now we'll keep it null. We will fill it later.
            token: null
        })
    }
    else {
        // if user does not exist, then we'll just create a 401 (Unauthorized).
        res.status(401);
        throw new Error('Invalid Email or Password!');
    }
});  


export {authUser};
*/








// ------------ VERSION 2 -------------------- //
// This is where we do our authentication bit
import asyncHandler from 'express-async-handler';
import User from '../models/userModel.js';
import generateToken from '../utils/generateToken.js';
// First we will authenticate the user and then get the token.
// Obviously this is going to be a POST request.
// Our route will be /api/users/login.
// as this is the backend we can use our asyncHandler instead of try catch for our
// async request.
// ** Remember that whenever you do a POST request. The JSON response you get back will always be 
// found in the request object's body key.
const authUser = asyncHandler( async (req, res) => {

    // Get the data from the request body
    const {email, password} = req.body;
    // get the  details of the user with that email
    const user = await User.findOne({email});

    // if the user exists
    // we check if the the entered password is right
    // The comparing is going to take time, which is why in our userModel
    // if you see, our function is async. So we must await here for the function to respond.
    // (Or else we would have to use .then() which is something we dont want to do.)
    if (user  &&  (await user.matchPassword(password))) {

        // now we can send some json data back.
        res.json({
            _id: user._id,
            name: user.name,
            email: user.email,
            isAdmin: user.isAdmin,
            // call generateToken function and pass the user's id
            // for payload.
            token: generateToken(user._id),
        })
    } else {
        // if user does not exist, then we'll just create a 401 (Unauthorized).
        res.status(401);
        throw new Error('Invalid Email or Password!');
    }
});  


export { authUser };
