Rails.application.routes.draw do
  get 'users/index'
  get 'bookings/user_bookings'
  get 'comments/reported'
  devise_for :users
  namespace :api do
    resources :products, only: [:index]
  end
  resources :carts do
    member do
      get :finalize
      post 'finalize'
    end
  end
  resources :bookings do
    member do
      get :restore
    end
  end
  delete 'users/:id', to: 'users#destroy', as: :admin_destroy_user
  resources :products
  resources :products do
    member do
      get :add_to_cart
      get :down
      post 'down'
    end
  end
  devise_for :admin_users, ActiveAdmin::Devise.config
  ActiveAdmin.routes(self)
  devise_for :models
  root 'pages#home'
  get 'pages/about'
  get 'pages/home'
  get 'pages/contact'
  resources :comments do
    member do
      post :create
    end
  end
  resources :comments do
    member do
      get :report
      get :undo_report
    end
  end
  resources :users
  namespace :api do
    get 'users/email_exists', to: 'users#email_exists'
    get 'users/email_correct', to: 'users#email_correct'
    resources :courses, only: [:index]
  end
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
