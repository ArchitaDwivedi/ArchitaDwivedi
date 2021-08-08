//----------------------- VERSION 1 --------------------//
import mongoose from 'mongoose';

// we are importing this for our password matching logic.
import bcrypt from 'bcryptjs';


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




// Password checking.
// Here we will use 'this' so we can refere to the user who is 
// accessing this function (because we want this to be available for every object.)
userSchema.methods.matchPassword = async function(enteredPassword) {
    // we are decrypting first then comparing
    // This user's password vs whatever was entered.
    return await bcrypt.compare(enteredPassword, this.password);
};




// building a model using our Schema
const User = mongoose.model('User', userSchema);


export default User;