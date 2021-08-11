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
    required: true,
  },
  email: {
    type: String,
    required: true,
    unique: true,
  },
  password: {
    type: String,
    required: true,
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
userSchema.methods.matchPassword = async function (enteredPassword) {
    // we are decrypting first then comparing
    // This user's password vs whatever was entered.
  return await bcrypt.compare(enteredPassword, this.password);
};


// it accepts a next automatically.
userSchema.pre('save', async function (next) {
    // once the user gives us the data i.e email, pass, name. We're
    // just checking if it is exactly the same or if it has been changed.

    // We're doing this because say tomorrow we build some logic that updates
    // things like the name,password,etc.
    // Now if someone updates the password i.e if they've entered a new password
    // then we know its been modified, only then do we really want to encrypt the password
    // On the other hand, if it is the same as before i.e if the user has not updated it. Then
    // we do not want to enrypt as it will already be excrypted.
  if (!this.isModified('password')) {
    next();
  }


    // salt- special string
    // so we're generating a special string that's 10 chars long
  const salt = await bcrypt.genSalt(10);
    // hash it using the salt
  this.password = await bcrypt.hash(this.password, salt);
});

// building a model using our Schema
const User = mongoose.model('User', userSchema);



export default User;
