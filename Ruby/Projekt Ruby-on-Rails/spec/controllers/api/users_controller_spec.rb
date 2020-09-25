require 'rails_helper'

RSpec.describe Api::UsersController do
  describe 'GET #email_exists' do
    subject { get :email_exists, params: { email: email } }
    let(:email) { 'user@example.com' }

    it do
      expect(subject).to be_successful
      expect(JSON.parse(subject.body)).to eq(false)
    end

    context 'when email is taken' do
      let(:user) { create :user }
      let(:email) { user.email }

      it do
        expect(subject).to be_successful
        expect(JSON.parse(subject.body)).to eq(true)
      end
    end
  end

  describe 'GET #email_correct' do
    subject { get :email_correct, params: { email: email } }
    let(:email) { 'user@example.com' }

    it do
      expect(subject).to be_successful
      expect(JSON.parse(subject.body)).to eq(true)
    end

    context 'when email is invalid - 1' do
      let(:email) { 'userexample' }

      it do
        expect(subject).to be_successful
        expect(JSON.parse(subject.body)).to eq(false)
      end
    end

    context 'when email is invalid - 2' do
      let(:email) { 'userexample.com' }

      it do
        expect(subject).to be_successful
        expect(JSON.parse(subject.body)).to eq(false)
      end
    end
  end
end
