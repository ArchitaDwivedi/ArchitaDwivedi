// This is where we do our authentication bit
import express from 'express';
const router = express.Router();
import {
  authUser,
  getUserProfile,
  registerUser,
  updateUserProfile,
} from '../controllers/userController.js';
import { protect } from '../middleware/authMiddleware.js';


// we're not doing router.route because we only have 1 route, so we dont
// need it.
router.route('/').post(registerUser);

router.post('/login', authUser);
// if a user tries to get their detail (This route obviously needs to be protected)
// even if they try to update their profile. we need to first check if its them
router.route('/profile').get(protect, getUserProfile).put(protect, updateUserProfile);


export default router;
