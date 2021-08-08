// This is where we do our authentication bit
import express from 'express';
import {authUser} from '../controllers/userController.js';


const router = express.Router();

// we're not doing router.route because we only have 1 route, so we dont
// need it.
router.post('/login', authUser);

export default router;