// This is our route protection
// To check if the token we get is good or not.
import jwt from 'jsonwebtoken';
// could throw an error so we need to handle that
import asyncHandler from 'express-async-handler';
import User from '../models/userModel.js';





// in middlewares there's always next as we know
const protect = asyncHandler(async (req, res, next) => {
 // Token is going to be sent from the frontend in the request header
  // In postman, Headers>key, in that under key we write "Authorization" and value 
  // "Bearer <encrypted token>". (Bearer, since user is the bearer of this token. There are 
  // many different types of tokens.)
  // In axios, we'll be doing something similar later.
  let token;

  if (
    req.headers.authorization &&
    req.headers.authorization.startsWith('Bearer')
  ) {
    try {
      token = req.headers.authorization.split(' ')[1];
      // we will be decoding the token now
      // We will use our JWT_SECRET to see if we ourselves signed it and not someone random.
      const decoded = jwt.verify(token, process.env.JWT_SECRET);
      // decoded is the payload which has iat, expiry and id.
      // So now we have the id, so we can find our user by id.

      // Once we have that, we will get the entire object 
      // from which we want everything but the password. 
      // Now we will create a user property on this req object. So, we will use select() and do
      // '-password', means ignore password.
      req.user = await User.findById(decoded.id).select('-password');
      next();
    } catch (error) {
      console.error(error);
      res.status(401);
      throw new Error('Not authorized, token failed');
    }
  }


    // this is in case our token does not exist i.e say our user was deleted and the
    // id in our old token causes some issues as the user does not exist. So we check whether or not
    // the token exists in the first place.
  if (!token) {
    res.status(401);
    throw new Error('Not authorized, token failed');
  }
});



// Admin auth middleware
const admin = (req, res, next) => {
  if (req.user && req.user.isAdmin) {
    next();
  } else {
    // Unauthorized
    res.status(401);
    throw new Error('Not authorized as an admin');
  }
};

export { protect, admin };
