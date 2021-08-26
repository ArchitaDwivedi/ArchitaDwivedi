import mongoose from 'mongoose';
// Building a schema i.e everything we 
// want in this Model -> username, password, etc

// An order can have 
// user -> the user whose order this is
// ...
const orderSchema = mongoose.Schema(
  {
    user: {
      // MongoDB's object id will get saved here
        // That object id will be of one of the users hence we've
        // given 'ref: User' 
      type: mongoose.Schema.Types.ObjectId,
      required: true,
      ref: 'User',
    },
    // just like reviewSchems in productModel. But
    // written directly, instead of making a schema separately
    orderItems: [
      {
        name: { type: String, required: true },
        qty: { type: Number, required: true },
        image: { type: String, required: true },
        price: { type: String, required: true },
        // product id of each product
        product: {
          type: mongoose.Schema.Types.ObjectId,
          required: true,
          ref: 'Product',
        },
      },
    ],
    shippingAddress: {
      address: { type: String, required: true },
      city: { type: String, required: true },
      postalCode: { type: String, required: true },
      country: { type: String, required: true },
    },
    paymentMethod: {
      type: String,
      required: true,
    },
    paymentResult: {
      id: { type: String },
      status: { type: String },
      update_time: { type: String },
      email_address: { type: String },
    },
    taxPrice: {
      type: Number,
      required: true,
      default: 0.0,
    },
    shippingPrice: {
      type: Number,
      required: true,
      default: 0.0,
    },
    totalPrice: {
      type: Number,
      required: true,
      default: 0.0,
    },
    isPaid: {
      type: Boolean,
      required: true,
      default: false,
    },
    paidAt: {
      type: Date,
    },
    isDelivered: {
      type: Boolean,
      required: true,
      default: false,
    },
    deliveredAt: { type: Date },
  },
  {
// Schema can take in more args
// by enabling this, we'll essentially
// log the time of when the order was placed
    timestamps: true,
  }
);
// building a model using our Schema
const Order = mongoose.model('Order', orderSchema);

export default Order;
