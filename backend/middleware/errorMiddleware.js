// This is the where we're building middlewares
const notFound = (req, res, next) => {
  const error = new Error(`Not Found - ${req.originalUrl}`);
  res.status(404);
 // assume you have multiple middlewares in your server.js
    // app.use() 1
    // app.use() 2
    // app.use() 3
    // So, if you're done with 1, 'next' will automatically send you to 2 and so on.
    // i.e it will send it to the next place the request has to go to.
  next(error);
};

const errorHandler = (err, req, res, next) => {
// asyncHandler often has some glitch due to which
    // it ends up sending status 200 even when theres an error.

    // Our res object will get populated where we're handling
    // our routes. So, we check the statusCode first.
    // if it is 200, we know its some glitch, so we change it to 500
    // otherwise we'll not change it.
  const statusCode = res.statusCode === 200 ? 500 : res.statusCode;
  res.status(statusCode);
  res.json({ message: err.message });
};

export { notFound, errorHandler };
