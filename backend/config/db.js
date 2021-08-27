// This is the file where we set up MongoDB
import mongoose from 'mongoose';


// This is where we form a connection with our
// MongoDB. It needs to be async ofcourse.
// We'll follow a common pattern where in we'll use try-catch
// with any async function
// These steps are all a requirement that MongoDB itself has stated.
const connectDB = async () => {
  try {
    const conn = await mongoose.connect(process.env.MONGO_URI, {
      useUnifiedTopology: true,
      useNewUrlParser: true,
      useCreateIndex: true,
    });
    // once connection is made
    console.log(`MongoDB Connected: ${conn.connection.host}`.cyan.underline);
  } catch (err) {
    console.error(`Error: ${err.message}`.red.underline.bold);
    // close server with error
    process.exit(1);
  }
};

export default connectDB;
