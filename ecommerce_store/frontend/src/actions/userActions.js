import axios from 'axios';
import {
    USER_LOGIN_REQUEST,
    USER_LOGIN_LOGOUT,
    USER_LOGIN_SUCCESS,
    USER_LOGIN_FAIL} from '../constants/userConstants';


// we'll accept an email and a password
export const login = (email, password) => async (dispatch) => {
    try{
        dispatch(USER_LOGIN_REQUEST);

        // So this is where we're posting our data to our backend, so we need to
        // specify the content type.
        // and so we're also attaching headers with our 'Authorization' (token) ,etc this time.
        const config = {
            headers: {
                'Content-Type': 'application/json',
            },
        };

        const {data} = await axios.post('/api/users/login',
        {email,password}, 
        config);

       dispatch({type: USER_LOGIN_SUCCESS, payload: data});
       
       localStorage.setItem('userInfo', JSON.stringify(data))
    } catch(error){
        dispatch({type: USER_LOGIN_FAIL,
            paylaod: error.response && error.response.data.message 
            ? error.response.data.message : error.message});
    }
}
