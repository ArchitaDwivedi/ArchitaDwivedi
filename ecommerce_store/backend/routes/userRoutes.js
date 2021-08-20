// This is where we do our authentication bit
import express from 'express';
const router = express.Router();
import {
  authUser,
  getUserProfile,
  registerUser,
  updateUserProfile,
  getUsers,
  deleteUser,
  updateUser,
  getUserById,
} from '../controllers/userController.js';
import { protect, admin } from '../middleware/authMiddleware.js';




// we're not doing router.route because we only have 1 route, so we dont
// need it.

// First, we protect our route first with protect, next to check and see
// if a user is an Admin we use the admin middleware
router.route('/').post(registerUser).get(protect, admin, getUsers);
router.post('/login', authUser);

// if a user tries to get their detail (This route obviously needs to be protected)
// even if they try to update their profile. we need to first check if its them 
router.route('/profile').get(protect, getUserProfile).put(protect, updateUserProfile);
router.route('/:id').get(protect, admin, getUserById).delete(protect, admin, deleteUser).put(protect, admin, updateUser);

export default router;
