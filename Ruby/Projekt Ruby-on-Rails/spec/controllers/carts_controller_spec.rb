require 'rails_helper'

RSpec.describe CartsController, type: :controller do
  describe 'GET #index' do
    subject { get :index }
    let(:admin) { create :admin_user }

    it do
      sign_in admin
      expect(subject.status).to eq(200)
    end
  end
end
