//----------------------- VERSION 1 --------------------//
import mongoose from 'mongoose';

// Building a schema i.e everything we 
// want in this Model -> username, password, etc


// A user can have 
// name
// email
// password
// role (isAdmin or not)
const userSchema = mongoose.Schema({
     name: {
         type: String,
         required: true
     },
     email: {
         type: String,
         required: true

     },
     password: {
         type: String,
         required: true
     },
     isAdmin: {
        type: Boolean,
        required: true,
        default: false,
     },
});

// building a model using our Schema
const User = mongoose.model('User', userSchema);


export default User;