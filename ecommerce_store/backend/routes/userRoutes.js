// This is where we do our authentication bit
import express from 'express';
import {authUser, getUserProfile,registerUser} from '../controllers/userController.js';
import {protect} from '../middleware/authMiddleware.js';

const router = express.Router();




router.route('/').post(registerUser);



// we're not doing router.route because we only have 1 route, so we dont
// need it.
router.post('/login', authUser);



// if a user tries to get their detail (This route obviously needs to be protected)
router.route('/profile').get(protect, getUserProfile);

export default router;