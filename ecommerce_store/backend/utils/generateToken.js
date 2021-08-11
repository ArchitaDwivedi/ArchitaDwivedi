// Creating JWT Token
import jwt from 'jsonwebtoken';

const generateToken = (id) => {
    // Now we will return a jwt.sign to create a token. We will give
    // and id to it. If we wanted we could give a name, etc as well.
    // Essentially anything that can go in a payload.

    // The second argument is our JWT String (Secret string).
    // Each time a token is created this string will be used for it. 
    // It should be strong and atleast 10 characters long.
    // So nobody random can send us any random token.
    // Remember, this must be kept safe. We will write this in our .env file
    // for now.
    // The last arg is some special options that we can give.
    // Eg:- expiry date, etc. Here our user will be authenticated for
    // 30 days.
  return jwt.sign({ id }, process.env.JWT_SECRET, { expiresIn: '30d' });
};

export default generateToken;
